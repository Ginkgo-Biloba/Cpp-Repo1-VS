#include "leetcode.hpp"

/* 526. 优美的排列

假设有从 1 到 N 的 N 个整数，如果从这 N 个数字中成功构造出一个数组，使得数组的第 i 位 (1 <= i <= N) 满足如下两个条件中的一个，我们就称这个数组为一个优美的排列。条件：

		第 i 位的数字能被 i 整除
		i 能被第 i 位上的数字整除

现在给定一个整数 N，请问可以构造多少个优美的排列？

示例1:
输入: 2
输出: 2
解释:
第 1 个优美的排列是 [1, 2]:
	第 1 个位置（i=1）上的数字是1，1能被 i（i=1）整除
	第 2 个位置（i=2）上的数字是2，2能被 i（i=2）整除
第 2 个优美的排列是 [2, 1]:
	第 1 个位置（i=1）上的数字是2，2能被 i（i=1）整除
	第 2 个位置（i=2）上的数字是1，i（i=2）能被 1 整除

说明:
		N 是一个正整数，并且不会超过15。
*/

class Solution
{
	int N, count;
	vector<int> perm;
	vector<char> nouse;

	inline bool beauty(int i, int n)
	{
		i = (i < n ? (n % i) : (i % n));
		return i == 0;
	}

	void dfs()
	{
		int len = static_cast<int>(perm.size());
		if (len == N)
		{
			++count;
			return;
		}
		int pos = len + 1;
		for (int i = 1; i <= N; ++i)
		{
			if (nouse[i] && beauty(i, pos))
			{
				perm.push_back(i);
				nouse[i] = 0;
				dfs();
				perm.pop_back();
				nouse[i] = 1;
			}
		}
	}

public:
	int countArrangement(int _N)
	{
		N = _N;
		perm.reserve(N);
		// 第 0 个废掉，太费事
		nouse.resize(N + 1);
		memset(nouse.data(), 1, (N + 1) * sizeof(char));
		count = 0;
		dfs();
		return count;
	}
};


int main()
{
	OutExpr(
		Solution().countArrangement(25),
		"%d");
}
