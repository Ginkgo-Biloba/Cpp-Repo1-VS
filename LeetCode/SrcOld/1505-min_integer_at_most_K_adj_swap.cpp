#include "leetcode.hpp"

/* 1505. 最多 K 次交换相邻数位后得到的最小整数

给你一个字符串 num 和一个整数 k 。
其中，num 表示一个很大的整数，字符串中的每个字符依次对应整数上的各个 数位 。

你可以交换这个整数相邻数位的数字 最多 k 次。
请你返回你能得到的最小整数，并以字符串形式返回。

示例 1：
https://assets.leetcode.com/uploads/2020/06/17/q4_1.jpg
输入：num = "4321", k = 4
输出："1342"
解释：4321 通过 4 次交换相邻数位得到最小整数的步骤如上图所示。

示例 2：
输入：num = "100", k = 1
输出："010"
解释：输出可以包含前导 0 ，但输入保证不会有前导 0 。

示例 3：
输入：num = "36789", k = 1000
输出："36789"
解释：不需要做任何交换。

示例 4：
输入：num = "22", k = 22
输出："22"

示例 5：
输入：num = "9438957234785635408", k = 23
输出："0345989723478563548"

提示：
	1 <= num.length <= 30000
	num 只包含 数字 且不含有 前导 0 。
	1 <= k <= 10^9
*/

class SegTree
{
	vector<int> sum;
	int len;

	int lowbit(int i)
	{
		return i & (-i);
	}

public:
	SegTree()
	{
		len = 32760;
		sum.resize(len);
	}

	void update(int i, int x)
	{
		++i;
		for (; i < len; i += lowbit(i))
			sum[i] += x;
	}

	int get(int i)
	{
		// 需要 +1 要不 0 那里退不出去循环
		++i;
		int r = 0;
		for (; i > 0; i -= lowbit(i))
			r += sum[i];
		return r;
	}
};

// https://www.youtube.com/watch?v=1wjYXKeGtOc
// 抄的
class Solution
{
public:
	string minInteger(string src, int k)
	{
		int len = static_cast<int>(src.size());
		SegTree sum;
		string dst;
		vector<int> idx[10];

		for (int i = len - 1; i >= 0; --i)
		{
			int n = src[i] - '0';
			idx[n].push_back(i);
			sum.update(i, 1);
		}

		while (k)
		{
			bool have = false;
			for (int n = 0; n < 10; ++n)
			{
				if (idx[n].empty())
					continue;
				int i = idx[n].back();
				int s = sum.get(i) - 1;
				if (s <= k)
				{
					have = true;
					k -= s;
					sum.update(i, -1);
					// src[i] == n + '0';
					dst.push_back(src[i]);
					idx[n].pop_back();
					src[i] = 'z';
					break;
				}
			}
			if (!have)
				break;
		}

		for (int i = 0; i < len; ++i)
		{
			if (src[i] != 'z')
				dst.push_back(src[i]);
		}
		return dst;
	}
};


int main()
{
	Solution s;
	// 124498948179
	OutString(s.minInteger("294984148179", 11));
	OutString(s.minInteger("4321", 4));
	OutString(s.minInteger("100", 1));
	OutString(s.minInteger("36789", 1000));
	OutString(s.minInteger("22", 22));
	// 0345989723478563548
	OutString(s.minInteger("9438957234785635408", 23));
	OutString(s.minInteger("", 4));
}
