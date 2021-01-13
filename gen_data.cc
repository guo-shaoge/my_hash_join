#include "multi_thread_hash_join.h"
#include <random>
using namespace std;

void gen_data(int row_cnt, vector<pair<int, int>>& rows, double ndv) {
  vector<int> all_vals(row_cnt, 0);
  std::iota(all_vals.begin(), all_vals.end(), 0);

  int dist_val_cnt = row_cnt * ndv;
  vector<int> dist_vals(all_vals.begin(), all_vals.begin() + dist_val_cnt);

  for (int i = 0; i < row_cnt; ++i) {
    int idx = i % dist_vals.size();
    rows.push_back({dist_vals[idx], rand()});
  }
}

void write_file(const vector<pair<int, int>>& rows, const string& fn) {
  ofstream out(fn);
  assert(out.is_open());

  for (int i = 0; i < rows.size(); ++i) {
    out << to_string(rows[i].first) << " " << to_string(rows[i].second) << endl;
  }
}

int main(int argc, char* argv[]) {
  int ret = 0;
  if (4 != argc) {
    ret = -1;
    cerr << "invalid arg cnt. ./gen_data row_cnt fn ndv\n";
  } else {
    int row_cnt = stoi(argv[1]);
    string fn(argv[2]);
    double ndv = stod(argv[3]);

    vector<pair<int, int>> rows;
    gen_data(row_cnt, rows, ndv);
    write_file(rows, fn);
  }
}
