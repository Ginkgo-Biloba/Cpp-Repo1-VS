#include "leetcode.hpp"

/* 967. 连续差相同的数字

返回所有长度为 N 且满足其每两个连续位上的数字之间的差的绝对值为 K 的非负整数。

请注意，除了数字 0 本身之外，答案中的每个数字都不能有前导零。
例如，01 因为有一个前导零，所以是无效的；但 0 是有效的。

你可以按任何顺序返回答案。

示例 1：
输入：N = 3, K = 7
输出：[181,292,707,818,929]
解释：注意，070 不是一个有效的数字，因为它有前导零。

示例 2：
输入：N = 2, K = 1
输出：[10,12,21,23,32,34,43,45,54,56,65,67,76,78,87,89,98]

提示：
	1 <= N <= 9
	0 <= K <= 9
*/

typedef array<int, 9> vi9;

vector<int> numsSameConsecDiff(int N, int K)
{
	vector<int> nums;
	if (N == 1)
	{
		for (int i = 0; i < 10; ++i)
			nums.push_back(i);
		return nums;
	}

	vector<vi9> cur, nxt;
	for (int i = 1; i < 10; ++i)
	{
		vi9 v = { i };
		cur.push_back(v);
	}

	// 广搜
	for (int n = 1; n < N; ++n)
	{
		nxt.clear();
		for (vi9 v : cur)
		{
			v[n] = v[n - 1] + K;
			if (static_cast<unsigned>(v[n]) < 10)
				nxt.push_back(v);
			if (K)
			{
				v[n] = v[n - 1] - K;
				if (static_cast<unsigned>(v[n]) < 10)
					nxt.push_back(v);
			}
		}
		nxt.swap(cur);
	}

	for (vi9 const& v : cur)
	{
		int s = 0;
		for (int n = 0; n < N; ++n)
			s = s * 10 + v[n];
		nums.push_back(s);
	}

	sort(nums.begin(), nums.end());
	return nums;
}

int main()
{
	char const* problem = "Numbers With Same Consecutive Differences";
	output(numsSameConsecDiff(3, 7), problem);
	output(numsSameConsecDiff(2, 1), problem);
	output(numsSameConsecDiff(1, 1), problem);
	output(numsSameConsecDiff(2, 0), problem);
}
