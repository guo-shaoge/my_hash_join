#!/bin/bash

cur_dir=$(dirname `readlink -f "$0"`)
cd ${cur_dir}/..

if [ $# != 0 ]; then
  echo // heavy key equal
  echo // join using 1 thread
  ./bin/my_hash_join_heavy_key_equal 1 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1
  
  echo // join using 2 thread
  ./bin/my_hash_join_heavy_key_equal 2 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1
  
  echo // join using 4 thread
  ./bin/my_hash_join_heavy_key_equal 4 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1
  
  echo // join using 8 thread
  ./bin/my_hash_join_heavy_key_equal 8 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1
else
  echo // join using 1 thread
  ./bin/my_hash_join 1 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1
  
  echo // join using 2 thread
  ./bin/my_hash_join 2 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1
  
  echo // join using 4 thread
  ./bin/my_hash_join 4 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1
  
  echo // join using 8 thread
  ./bin/my_hash_join 8 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1
fi
