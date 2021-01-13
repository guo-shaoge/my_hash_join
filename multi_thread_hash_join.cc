#include "multi_thread_hash_join.h"
#include <chrono>

using namespace std;
using namespace chrono;

// check if r1.b > r2.b
bool greater_expression(const pair<int, int>& r1, const pair<int, int>& r2) {
  return r1.second > r2.second;
}

template<typename T>
void output_time(const T& start, const T& end, string desc) {
  auto duration = duration_cast<microseconds>(end - start);
  cout << desc << ": " << double(duration.count()) *
                          microseconds::period::num /
                          microseconds::period::den << " seconds" << endl;
}

void output_hash_table_info(const unordered_multimap<int, pair<int, int>, decltype(g_hasher), decltype(g_key_equal)>& h) {
  cout << "bucket_count: " << h.bucket_count() << endl;
  cout << "load_factor: " << h.load_factor() << endl;
  for (int i = 0; i < h.bucket_count(); ++i) {
    cout << h.bucket_size(i) << endl;
  }
}

int scan_file(const string& fn, vector<pair<int, int>>& rows) {
  int ret = 0;
  ifstream in(fn);
  if (!in.is_open()) {
    ret = -1;
    cerr << "open " << fn << " failed\n";
  } else {
    string row;
    string col1;
    string col2;
    const char delim = ' ';
    while (getline(in, row)) {
      stringstream line_stream(row);
      int col_cnt = 0;
      if (!getline(line_stream, col1, delim) || !getline(line_stream, col2, delim)) {
        ret = -1;
        cerr << "parse row failed\n";
        break;
      } else {
        // TODO: may throw exception when got invalid number
        int col1_int = stoi(col1);
        int col2_int = stoi(col2);
        rows.push_back(pair<int, int>{col1_int, col2_int});
      }
    }
  }
  return ret;
}

// rows.size(): 250 rows
// thread cnt : 3
// pos_vec: 0, 84, 168, 250
int split_rows(const vector<pair<int, int>>& rows,
               int thread_cnt,
               vector<int>& pos_vec) {
  int ret = 0;
  if (rows.empty() || thread_cnt <= 0 || rows.size() <= thread_cnt) {
    ret = -1;
    cerr << "split_rows error\n";
  } else {
    int cur_pos = 0;
    int remain = (rows.size() % thread_cnt == 0) ? 0 : 1;
    int step = rows.size() / thread_cnt + remain;
    do {
      pos_vec.push_back(cur_pos);
      cur_pos += step;
    } while (cur_pos < rows.size());

    if (cur_pos >= rows.size()) {
      pos_vec.push_back(rows.size());
    }
  }
  return ret;
}

int build_hash_table(const vector<pair<int, int>>& rows,
                     unordered_multimap<int, pair<int, int>, decltype(g_hasher), decltype(g_key_equal)>& hash_table) {
  int ret = 0;
  if (rows.empty()) {
    ret = -1;
    cerr << "rows is empty\n";
  } else {
    for (const auto& r : rows) {
      hash_table.insert({r.first, {r.first, r.second}});
    }
  }
  return ret;
}

void do_hash_join_per_thread(const unordered_multimap<int, pair<int, int>, decltype(g_hasher), decltype(g_key_equal)>& hash_table,
                             const vector<pair<int, int>>& probe_rows,
                             const vector<int>& pos_vec,
                             const int thread_id,
                             const OtherCondFunc& other_cond_func,
                             promise<int>&& res_promise) {
  int count_res = 0;
  assert(thread_id + 1 <= pos_vec.size());

  int pos_beg = pos_vec[thread_id];
  int pos_end = pos_vec[thread_id + 1];
  assert(pos_end > pos_beg && pos_end <= probe_rows.size());

  for (int i = pos_beg; i < pos_end; ++i) {
    const pair<int, int>& row = probe_rows[i];
    auto range = hash_table.equal_range(row.first);
    for (auto it = range.first; it != range.second; ++it) {
      if (other_cond_func(row, it->second)) {
        ++count_res;
      }
    }
  }
  res_promise.set_value(count_res);
}

void my_hash_join(int thread_cnt, int bucket_cnt, const string& fn1, const string& fn2,
                  int& count_res) {
  int ret = 0;
  vector<pair<int, int>> rows1;
  vector<pair<int, int>> rows2;

  auto start = system_clock::now();
  ASSERT_SUCC(scan_file(fn1, rows1));
  ASSERT_SUCC(scan_file(fn2, rows2));
  auto end = system_clock::now();
  output_time(start, end, "scan_file");

  vector<pair<int, int>>* outer_rows = &rows1;
  vector<pair<int, int>>* inner_rows = &rows2;

  vector<int> pos_vec;
  ASSERT_SUCC(split_rows(*outer_rows, thread_cnt, pos_vec));

  start = system_clock::now();
  unordered_multimap<int, pair<int, int>, decltype(g_hasher), decltype(g_key_equal)> hash_table(bucket_cnt, g_hasher, g_key_equal);
  ASSERT_SUCC(build_hash_table(*inner_rows, hash_table));
  end = system_clock::now();
  output_time(start, end, "build_hash_table");
#ifdef DEBUG_HASH_TBL
  output_hash_table_info(hash_table);
#endif

  vector<thread> threads;
  vector<promise<int>> count_pro_vec(thread_cnt);
  vector<future<int>> count_fut_vec;
  for (int i = 0; i < thread_cnt; ++i) {
    count_fut_vec.push_back(count_pro_vec[i].get_future());
  }

  start = system_clock::now();
  for (int i = 0; i < thread_cnt; ++i) {
    threads.push_back(std::thread(do_hash_join_per_thread, 
                                  hash_table,
                                  *outer_rows,
                                  pos_vec,
                                  i,
                                  greater_expression,
                                  std::move(count_pro_vec[i])));
  }

  count_res = 0;
  for (int i = 0; i < thread_cnt; ++i) {
    int tmp = count_fut_vec[i].get();
    assert(tmp >= 0);
    count_res += tmp;
  }

  for (int i = 0; i < thread_cnt; ++i) {
    threads[i].join();
  }
  end = system_clock::now();
  output_time(start, end, "do_hash_join_per_thread and join all thread");
}

