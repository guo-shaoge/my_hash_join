all: my_hash_join unitest gen_data compute_ndv my_hash_join_debug_hash_tbl my_hash_join_heavy_key_equal

my_hash_join_debug_hash_tbl:
	g++ -std=c++11 -pthread multi_thread_hash_join.cc main.cc -o my_hash_join_debug_hash_tbl -DDEBUG_HASH_TBL
my_hash_join_heavy_key_equal:
	g++ -std=c++11 -pthread multi_thread_hash_join.cc main.cc -o my_hash_join_heavy_key_equal -DHEAVY_KEY_EQUAL
my_hash_join:
	g++ -std=c++11 -pthread multi_thread_hash_join.cc main.cc -o my_hash_join
unitest:
	g++ -std=c++11 -pthread multi_thread_hash_join.cc unitest.cc -o unitest
gen_data:
	g++ -std=c++11 gen_data.cc -o gen_data
compute_ndv:
	g++ -std=c++11 -pthread multi_thread_hash_join.cc compute_ndv.cc -o compute_ndv
clean:
	rm -rf my_hash_join unitest gen_data compute_ndv my_hash_join_debug_hash_tbl my_hash_join_heavy_key_equal
