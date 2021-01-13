#!/bin/bash
# echo '-- left tbl ndv: min'
# echo '<<right tbl ndv: min>>'
# ./my_hash_join 1 500 ./dataset/ndv_0_8_f1_500w ./dataset/all_same_f1_500w
# 
# echo '<<right tbl ndv: 0.1>>'
# ./my_hash_join 1 500 ./dataset/ndv_0_8_f1_500w ./dataset/ndv_0_1_f1_500w
# 
# echo '<<right tbl ndv: 0.3>>'
# ./my_hash_join 1 500 ./dataset/ndv_0_8_f1_500w ./dataset/ndv_0_3_f1_500w
# 
# echo '<<right tbl ndv: 0.5>>'
# ./my_hash_join 1 500 ./dataset/ndv_0_8_f1_500w ./dataset/ndv_0_5_f1_500w
# 
# echo '<<right tbl ndv: 0.7>>'
# ./my_hash_join 1 500 ./dataset/ndv_0_8_f1_500w ./dataset/ndv_0_7_f1_500w
# 
# echo '<<right tbl ndv: 0.7>>'
# ./my_hash_join 1 500 ./dataset/ndv_0_8_f1_500w ./dataset/ndv_0_8_f1_500w

# ./my_hash_join 1 500 ./dataset/ndv_0_9_f1_500w  ./dataset/ndv_0_1_f1_500w
# ./my_hash_join 1 500 ./dataset/ndv_0_9_f1_500w  ./dataset/ndv_0_5_f1_500w
# ./my_hash_join 1 500 ./dataset/ndv_0_9_f1_500w  ./dataset/ndv_0_7_f1_500w
# ./my_hash_join 1 500 ./dataset/ndv_0_9_f1_500w  ./dataset/ndv_0_8_f1_500w

./my_hash_join_heavy_key_equal 1 500 ./dataset/ndv_0_9_f1_500w  ./dataset/ndv_0_1_f1_500w
./my_hash_join_heavy_key_equal 1 500 ./dataset/ndv_0_9_f1_500w  ./dataset/ndv_0_5_f1_500w
./my_hash_join_heavy_key_equal 1 500 ./dataset/ndv_0_9_f1_500w  ./dataset/ndv_0_7_f1_500w
./my_hash_join_heavy_key_equal 1 500 ./dataset/ndv_0_9_f1_500w  ./dataset/ndv_0_8_f1_500w
