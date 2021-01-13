#!/bin/bash

cur_dir=$(dirname `readlink -f "$0"`)
cd ${cur_dir}/..

echo 'one thread, using heavy_key_equal'
echo 'left tbl ndv: 0.9, right tbl ndv: 0.1'
./bin/my_hash_join_heavy_key_equal 1 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1
echo 'left tbl ndv: 0.9, right tbl ndv: 0.5'
./bin/my_hash_join_heavy_key_equal 1 500 ./dataset/ndv_0_9  ./dataset/ndv_0_5
echo 'left tbl ndv: 0.9, right tbl ndv: 0.7'
./bin/my_hash_join_heavy_key_equal 1 500 ./dataset/ndv_0_9  ./dataset/ndv_0_7
echo 'left tbl ndv: 0.9, right tbl ndv: 1'
./bin/my_hash_join_heavy_key_equal 1 500 ./dataset/ndv_0_9  ./dataset/ndv_1
