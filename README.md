## 实现逻辑
采用多线程模型。逻辑如下：

主线程工作：
1. 读取两个csv文件，将所有内容放入内存，得到inner_table_rows/outer_table_rows
2. 将outer_table_rows数组按照线程数均分，每个线程相同大小的workload
3. 根据inner_table_rows数组构造hash表。这里使用C++中unordered_multimap
4. 启动多个线程，每个线程根据自己的workload，从hash表中进行查找，查找时同时计算是否满足非等之条件
5. 主线程等待各个线程执行结果，对count数目进行汇总

1到3，都是由主线程完成。第4步由多个线程完成，各个线程会根据自己的workload划分，从hash表中进行查找

## 测试
### 正确性
1. 包含一个简单的单测
2. 使用pg进行验证，结果一致

### 性能测试

## ndv的影响
理论上，如果ndv比较小，可能会导致hash表某个桶很大，可能会退化成nested loop
join，失去了构造hash表的意义。造成某个值命中该桶后，需要进行的比较操作会很多。导致速度变慢

但是测试发现，结论正好相反。见如下表格：

左表ndv固定为0.8(./my_hash_join 1 500 ./dataset/all_same_f1_500w ./dataset/all_same_f1_500w)

右表ndv | 时间
0.1 | 2.87s
0.5 | 2.56s
0.7 | 2.31s
0.8 | 2.29s

右表ndv | 时间
0.1 | 2.6s
0.5 | 3.0s
0.7 | 3.2s
0.8 | 3.3s

## 数据集生成
  make
  ./gen_data 5000000 0.8 ./dataset/ndv_0_8_f1
