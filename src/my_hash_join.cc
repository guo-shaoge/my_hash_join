#include "multi_thread_hash_join.h"
using namespace std;

// ./my_hash_join thread_cnt file1 file2
int main(int argc, char* argv[]) {
  int ret = 0;
  if (argc != 5) {
    ret = -1;
    cerr << "invalid arg cnt. ./my_hash_join thread_cnt bucket_cnt file1 file2\n";
  } else {
    int count_res = -1;
    int thread_cnt = std::stoi(argv[1]);
    int bucket_cnt = std::stoi(argv[2]);
    string fn1(argv[3]);
    string fn2(argv[4]);
    my_hash_join(thread_cnt, bucket_cnt, fn1, fn2, count_res);

    cout << "count res: " << count_res << endl << endl;
  }
  return ret;
}
