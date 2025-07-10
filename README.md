# GameOfLife

# Features
1.  使用cmake进行代码管理
2.  集成了webgpu, glfw 等第三方库

GameofLife 算法特点:
1. 一次演化的时间复杂度是n*log(n), 其中的n是Life生命的数量, 这个应该是演化的最优解了:) 多线程???
2. 利用std::set内元素的有序特性, 对Life生命做拓扑排序, 优化查找时间(查找时间为log(n))
3. 大整数不用特殊处理, 就是一个std::int64_t数据类型. 由于计算机整数是一个环, 溢出的话会直接从宇宙另一边出现.
4. 使用allocator对Life做内存分配.
