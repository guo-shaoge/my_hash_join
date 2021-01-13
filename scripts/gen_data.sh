#!/bin/bash

cur_dir=$(dirname `readlink -f "$0"`)
cd ${cur_dir}/..

echo '// ndv 0.1 ing'
./bin/gen_data 5000000 ./dataset/ndv_0_1 0.1
echo '// ndv 0.5 ing'
./bin/gen_data 5000000 ./dataset/ndv_0_5 0.5
echo '// ndv 0.7 ing'
./bin/gen_data 5000000 ./dataset/ndv_0_7 0.7
echo '// ndv 0.9 ing'
./bin/gen_data 5000000 ./dataset/ndv_0_9 0.9
echo '// ndv 1 ing'
./bin/gen_data 5000000 ./dataset/ndv_1 1
