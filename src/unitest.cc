#include "multi_thread_hash_join.h"
#include <random>
using namespace std;

void gen_data(int row_cnt, vector<pair<int, int>>& rows) {
  for (int i = 0; i < row_cnt; ++i) {
    int c1 = rand();
    int c2 = rand();
    rows.push_back({c1, c2});
  }
}

void test_scan_file() {
  const string fn = "./dataset/unitest_scan_file";
  // basic test
  ofstream out(fn);
  assert(out.is_open());
  const int row_cnt = 4;
  const int col_cnt = 2;

  // generate data
  vector<pair<int, int>> rows;
  gen_data(row_cnt, rows);

  // write rows
  for (int i = 0; i < row_cnt; ++i) {
    out << to_string(rows[i].first) << " " << to_string(rows[i].second) << endl;
  }

  // test scan_file
  vector<pair<int, int>> new_rows;
  assert(scan_file(fn, new_rows) == 0);

  // check if is same
  assert(rows.size() == new_rows.size());
  for (int i = 0; i < rows.size(); ++i) {
    assert(rows[i].first == new_rows[i].first);
    assert(rows[i].second == new_rows[i].second);
  }
  cout << "test_scan_file SUCC\n";
}

void test_split_rows() {
  const int row_cnt = 250;
  const int thread_cnt = 3;
  vector<pair<int, int>> rows;
  gen_data(row_cnt, rows);

  vector<int> pos_vec;
  assert(rows.size() == row_cnt);
  assert(split_rows(rows, thread_cnt, pos_vec) == 0);
  assert(pos_vec.size() == thread_cnt + 1);
  for (auto v : pos_vec) {
    cout << v << endl;
  }
}

int main() {
  test_scan_file();
  test_split_rows();
}
