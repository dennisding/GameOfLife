# GameOfLife

# 怎么编译
1. mkdir GameOfLife
2. git clone https://github.com/dennisding/GameOfLife.git GameOfLife
3. cd GameOfLife
4. cmake_build.cmd  (window下有效, 目前没在其它平台测试)
5. 进入build目录, 打开GameOfLife.sln, 
5. 直接进行编译, 其中, GameOfLife是面试题目的要求项目, GameOfLifeGui是基于webgpu的可视化版本, 
	GameOfLifeLib是核心算法库, game是游戏引擎相关内容, wgpu是对glfw和webgup的封装,
	glfw3webgpu, glfw和webgpu是第三方库.

6. GameOfLifeGui的三个按钮, 从左到右分别是演化一次, 自动演化和停止自动演化.

# GameofLife 算法特点:
1. 一次演化的时间复杂度是n*log(n), 其中的n是Life生命的数量, 这个应该是演化的最优解了.
2. 利用std::set内元素的有序特性, 对Life生命做拓扑排序, 优化查找邻居的时间(查找时间为log(n))
3. 大整数不用特殊处理, 就是一个std::int64_t数据类型. 由于计算机整数是一个环, 溢出的话会直接从宇宙另一边出现.
4. 使用allocator对Life做内存分配.
5. 采用了一定的空间换迭代时间的方法,空间复杂度3n, n是生命的数量.
6. lock free 多线程内存分配和场景自动演化.