#include "leetcode.hpp"

/* 710. 黑名单中的随机数

给定一个包含 [0，n ) 中独特的整数的黑名单 B，写一个函数从 [ 0，n ) 中返回一个不在 B 中的随机整数。
对它进行优化使其尽量少调用系统方法 Math.random() 。

提示:
	1 <= N <= 1000000000
	0 <= B.length < min(100000, N)
	[0, N) 不包含 N，详细参见 interval notation 。

示例 1:
输入:
["Solution","pick","pick","pick"]
[[1,[]],[],[],[]]
输出: [null,0,0,0]

示例 2:
输入:
["Solution","pick","pick","pick"]
[[2,[]],[],[],[]]
输出: [null,1,1,1]

示例 3:
输入:
["Solution","pick","pick","pick"]
[[3,[1]],[],[],[]]
Output: [null,0,0,2]

示例 4:

输入:
["Solution","pick","pick","pick"]
[[4,[2]],[],[],[]]
输出: [null,1,3,1]

输入语法说明：
输入是两个列表，调用成员函数名和调用的参数。
Solution的构造函数有两个参数，N 和黑名单 B。
pick 没有参数，输入参数是一个列表，即使参数为空，也会输入一个 [] 空列表。
*/

class OldSolution
{
	vector<int> black;
	double ratio;
	std::mt19937 mt;

public:
	OldSolution(int N, vector<int>& blacklist)
	{
		black.swap(blacklist);
		sort(black.begin(), black.end());
		N -= static_cast<int>(black.size());
		// mt.seed(0);
		ratio = N / (1.0 + mt.max());
	}

	int pick()
	{
		int n = static_cast<int>(ratio * mt());
		auto it = lower_bound(black.begin(), black.end(), n);
		auto itend = black.end();
		n += static_cast<int>(it - black.begin());
		for (; it != itend && (*it <= n); ++it)
			++n;
		return n;
	}
};

// https://leetcode.com/problems/random-pick-with-blacklist/discuss/144624/Java-O(B)-O(1)-HashMap
// 抄的
class Solution
{
	std::map<int, int> bw;
	double ratio;
	std::mt19937 mt;

public:
	Solution(int N, vector<int> const& black)
	{
		int M = N - static_cast<int>(black.size());
		ratio = M / (1.0 + mt.max());
		for (int b : black)
			bw[b] = -1;
		--N;
		for (int b : black)
			if (b < M)
			{
				// 需要映射
				while (bw.find(N) != bw.end())
					--N;
				bw[b] = N;
				--N;
			}
	}

	int pick()
	{
		int n = static_cast<int>(ratio * mt());
		if (bw.find(n) != bw.end())
			n = bw[n];
		return n;
	}
};


int main()
{
	vector<int> black = { 1, 2 };
	Solution s(6, black);
	for (int n = 10; n; --n)
		OutExpr(s.pick(), "%d");
}
