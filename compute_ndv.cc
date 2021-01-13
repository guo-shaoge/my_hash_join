#include "multi_thread_hash_join.h"
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
  int ret = 0;
  if (2 != argc) {
    ret = -1;
    cerr << "invalid arg cnt./compute_ndv fn\n";
  } else {
    unordered_set<int> s;
    string fn(argv[1]);
    vector<pair<int, int>> rows;
    assert(scan_file(fn, rows) == 0);
    for (const auto& r : rows) {
      s.insert(r.first);
    }
    cout << "dist val num: " << s.size() << ", total size: " << rows.size() << endl;
    cout << "ndv: " << (double)s.size() / rows.size() << endl;
  }
  return ret;
}
