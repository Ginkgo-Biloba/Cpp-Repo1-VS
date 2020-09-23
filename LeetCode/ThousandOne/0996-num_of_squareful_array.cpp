#include "leetcode.hpp"

/* 996. 正方形数组的数目

给定一个非负整数数组 A，如果该数组每对相邻元素之和是一个完全平方数，则称这一数组为正方形数组。

返回 A 的正方形排列的数目。
两个排列 A1 和 A2 不同的充要条件是存在某个索引 i，使得 A1[i] != A2[i]。

示例 1：
输入：[1,17,8]
输出：2
解释：
[1,8,17] 和 [17,8,1] 都是有效的排列。

示例 2：
输入：[2,2,2]
输出：1

提示：
	1 <= A.length <= 12
	0 <= A[i] <= 1e9
*/

class Solution
{
	struct SS
	{
		short f, i;
	};

	enum
	{
		PSIZE = (1 << 12) * 12,
	};

	int fact[13];
	char adj[12][12];
	int len, target;
	vector<int> path; // 11! = 39916800 < 2147483647
	vector<SS> current, nextstep;

	bool issquare(int x)
	{
		int y = static_cast<int>(::sqrt(x));
		return y * y == x;
	}

	int addto(SS const& ss, int d)
	{
		int i = ss.f * len + ss.i;
		path[i] += d;
		return path[i];
	}

public:
	Solution()
	{
		fact[0] = 1;
		for (int i = 1; i <= 12; ++i)
			fact[i] = fact[i - 1] * i;
	}

	int numSquarefulPerms(vector<int>& A)
	{
		len = static_cast<int>(A.size());
		target = (1 << len) - 1;
		path.resize(PSIZE);
		memset(path.data(), 0, sizeof(path[0]) * PSIZE);

		// 邻接表
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < len; ++i)
			for (int k = i + 1; k < len; ++k)
			{
				if (issquare(A[i] + A[k]))
					adj[i][k] = adj[k][i] = 1;
			}

		// 广搜
		SS ss;
		current.clear();
		for (int i = 0; i < len; ++i)
		{
			ss.f = static_cast<short>(1 << i);
			ss.i = static_cast<short>(i);
			current.push_back(ss);
			addto(ss, 1);
		}
		while (!current.empty())
		{
			nextstep.clear();
			for (SS cur : current)
			{
				int d = addto(cur, 0);
				for (int i = 0; i < len; ++i)
					if (adj[cur.i][i])
					{
						ss.f = static_cast<short>(cur.f | (1 << i));
						if (ss.f == cur.f)
							continue;
						ss.i = static_cast<short>(i);
						if (addto(ss, d) == d)
							nextstep.push_back(ss);
					}
			}
			nextstep.swap(current);
		}

		// 累加
		int sum = 0;
		ss.f = static_cast<short>(target);
		for (int i = 0; i < len; ++i)
		{
			ss.i = static_cast<short>(i);
			sum += addto(ss, 0);
		}

		// 去重
		sort(A.begin(), A.end());
		for (int i = 0; i < len;)
		{
			int k = i + 1;
			while (k < len && A[k] == A[i])
				++k;
			sum /= fact[k - i];
			i = k;
		}
		return sum;
	}
};


int main()
{
	vector<int>
		a = { 1, 17, 8 },
		b = { 2, 2, 2 },
		c = { 1, 1, 1, 1, 1, 1, 1, 1 };
	Solution s;
	OutExpr(s.numSquarefulPerms(a), "%d");
	OutExpr(s.numSquarefulPerms(b), "%d");
	OutExpr(s.numSquarefulPerms(c), "%d");
}
