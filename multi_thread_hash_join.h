#ifndef MULTI_THREAD_HASH_JOIN_H_
#define MULTI_THREAD_HASH_JOIN_H_

#include <stdlib.h>
#include <assert.h>

#include <vector>
#include <future>
#include <thread>
#include <unordered_map>
#include <functional>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>

#define ASSERT_SUCC(val) assert(val == 0)

auto g_hasher = [](int v) { return std::hash<int>()(v); };
auto g_key_equal = [](int v1, int v2) {
#ifdef HEAVY_KEY_EQUAL
  int i = 0;
  while (i < 500) ++i;
#endif
  return v1 == v2;
};

using OtherCondFunc = std::function<bool(const std::pair<int, int>&, const std::pair<int, int>&)>;
using MyHashMap = std::unordered_multimap<int, std::pair<int, int>, decltype(g_hasher), decltype(g_key_equal)>;

int scan_file(const std::string& fn, std::vector<std::pair<int, int>>& rows);
int split_rows(const std::vector<std::pair<int, int>>& rows,
               int thread_cnt,
               std::vector<int>& pos_vec);
int build_hash_table(const std::vector<std::pair<int, int>>& rows,
                     MyHashMap& hash_table);
void do_hash_join_per_thread(const MyHashMap& hash_table,
                             const std::vector<std::pair<int, int>>& probe_rows,
                             const std::vector<int>& pos_vec,
                             const int thread_id,
                             const OtherCondFunc& other_cond_func,
                             std::promise<int>&& res_promise);
void my_hash_join(int thread_cnt,
                  int bucket_cnt,
                  const std::string& fn1,
                  const std::string& fn2,
                  int& count_res);

#endif
