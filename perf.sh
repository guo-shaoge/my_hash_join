#!/bin/bash
./gen_data.sh

make clean
make -j

echo // 1 thread
./my_hash_join 1 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1

echo // 2 thread
./my_hash_join 2 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1

echo // 4 thread
./my_hash_join 4 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1

echo // 8 thread
./my_hash_join 8 500 ./dataset/ndv_0_9  ./dataset/ndv_0_1
