#include "leetcode.hpp"

/* 519. 随机翻转矩阵

题中给出一个 n 行 n 列的二维矩阵 (n_rows,n_cols)，且所有值被初始化为 0。要求编写一个 flip 函数，均匀随机的将矩阵中的 0 变为 1，并返回该值的位置下标 [row_id,col_id]；同样编写一个 reset 函数，将所有的值都重新置为 0。尽量最少调用随机函数 Math.random()，并且优化时间和空间复杂度。

注意:

1.1 <= n_rows, n_cols <= 10000

2. 0 <= row.id < n_rows 并且 0 <= col.id < n_cols

3.当矩阵中没有值为 0 时，不可以调用 flip 函数

4.调用 flip 和 reset 函数的次数加起来不会超过 1000 次

示例 1：

输入:
["Solution","flip","flip","flip","flip"]
[[2,3],[],[],[],[]]
输出: [null,[0,1],[1,2],[1,0],[1,1]]

示例 2：

输入:
["Solution","flip","flip","reset","flip"]
[[1,2],[],[],[],[]]
输出: [null,[0,0],[0,1],null,[0,0]]

输入语法解释：

输入包含两个列表：被调用的子程序和他们的参数。Solution 的构造函数有两个参数，分别为 n_rows 和 n_cols。flip 和 reset 没有参数，参数总会以列表形式给出，哪怕该列表为空。
*/

// https://leetcode-cn.com/problems/random-flip-matrix/solution/hei-ming-dan-dao-bai-ming-dan-de-ying-she-by-xii00/

class Solution
{
	int rows, cols, size;
	std::map<int, int> map;
	std::mt19937 mt;

public:
	Solution(int n_rows, int n_cols)
		: rows(n_rows)
		, cols(n_cols)
	{
		reset();
	}

	vector<int> flip()
	{
		vector<int> p(2);
		int cur = static_cast<int>(mt() >> 1) % size;
		int val = cur;
		--size;
		if (cur == size)
		{
			if (map.find(cur) != map.end())
			{
				val = map[cur];
				map.erase(cur);
			}
		}
		else
		{
			if (map.find(cur) != map.end())
				val = map[cur];
			if (map.find(size) != map.end())
			{
				map[cur] = map[size];
				map.erase(size);
			}
			else
				map[cur] = size;
		}

		p[0] = val / cols;
		p[1] = val % cols;
		return p;
	}

	void reset()
	{
		size = rows * cols;
		map.clear();
	}
};


int main()
{
	Solution s(2, 3);
	vector<int> p;
	p = s.flip();
	printf("%d, %d\n", p[0], p[1]);
	p = s.flip();
	printf("%d, %d\n", p[0], p[1]);
	p = s.flip();
	printf("%d, %d\n", p[0], p[1]);
	p = s.flip();
	printf("%d, %d\n", p[0], p[1]);
	p = s.flip();
	printf("%d, %d\n", p[0], p[1]);
	p = s.flip();
	printf("%d, %d\n", p[0], p[1]);
	// s.reset();
	// p = s.flip(); printf("%d, %d\n", p[0], p[1]);
}
