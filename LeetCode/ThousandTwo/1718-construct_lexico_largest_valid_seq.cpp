#include "leetcode.hpp"

/* 1718. 构建字典序最大的可行序列

给你一个整数 n ，请你找到满足下面条件的一个序列：
	整数 1 在序列中只出现一次。
	2 到 n 之间每个整数都恰好出现两次。
	对于每个 2 到 n 之间的整数 i ，两个 i 之间出现的距离恰好为 i 。

序列里面两个数 a[i] 和 a[j] 之间的 距离 ，我们定义为它们下标绝对值之差 |j - i| 。

请你返回满足上述条件中 字典序最大 的序列。
题目保证在给定限制条件下，一定存在解。

一个序列 a 被认为比序列 b （两者长度相同）字典序更大的条件是：
	a 和 b 中第一个不一样的数字处，a 序列的数字比 b 序列的数字大。
比方说，[0,1,9,0] 比 [0,1,5,6] 字典序更大，因为第一个不同的位置是第三个数字，且 9 比 5 大。

示例 1：
输入：n = 3
输出：[3,1,2,3,2]
解释：[2,3,2,1,3] 也是一个可行的序列，但是 [3,1,2,3,2] 是字典序最大的序列。

示例 2：
输入：n = 5
输出：[5,3,1,4,3,5,2,4,2]

提示：
	1 <= n <= 20
*/


class Solution
{
	vector<int> A, C;
	int stop, num, len;

	void dfs(int i)
	{
		for (; i < len; ++i)
		{
			if (A[i] == 0)
				break;
		}
		if (i == len)
			stop = 1;
		if (stop)
			return;
		for (int k = num; k > 0; --k)
		{
			if (C[k])
				continue;
			if (k == 1)
			{
				C[k] = 1;
				A[i] = k;
				dfs(i + 1);
				if (stop)
					return;
				C[k] = 0;
				A[i] = 0;
			}
			else
			{
				if (i + k >= len || A[i + k] > 0)
					continue;
				C[k] = 1;
				A[i] = A[i + k] = k;
				dfs(i + 1);
				if (stop)
					return;
				A[i] = A[i + k] = 0;
				C[k] = 0;
			}
		}
	}

public:
	vector<int> constructDistancedSequence(int n)
	{
		stop = 0;
		num = n;
		len = 2 * n - 1;
		A.assign(len, 0);
		C.assign(num + 1, 0);
		dfs(0);
		return A;
	}
};

int main()
{
	Solution s;
	output(s.constructDistancedSequence(3), "sequence");
	output(s.constructDistancedSequence(5), "sequence");
}
