#!/bin/bash
make -j

./gen_data 5000000 ./dataset/ndv_0_1 0.1
./gen_data 5000000 ./dataset/ndv_0_5 0.5
./gen_data 5000000 ./dataset/ndv_0_7 0.7
./gen_data 5000000 ./dataset/ndv_0_9 0.9
./gen_data 5000000 ./dataset/ndv_1 1
