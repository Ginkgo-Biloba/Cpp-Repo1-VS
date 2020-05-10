#include "leetcode.hpp"

/* 90. 子集 II

给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

示例:

输入: [1,2,2]
输出:
[
	[2],
	[1],
	[1,2,2],
	[2,2],
	[1,2],
	[]
]
*/

vector<vector<int>> subsetsWithDup(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	vector<vector<int>> R(1);
	int cap = 1, pre = 0, cur = 1;
	sort(A.begin(), A.end());
	for (int i = 0; i < len;)
	{
		int k = i + 1;
		for (; k < len; ++k)
		{
			if (A[i] != A[k])
				break;
		}
		cap *= k - i + 1;
		i = k;
	}
	R.reserve(cap);
	for (int i = 0; i < len; ++i)
	{
		int h = i - 1;
		int a = A[i], c = 0;
		pre = cur;
		cur = static_cast<int>(R.size());
		// 重复的话，只有上次添加过当前数字的才能接着添加
		if (0 <= h && A[h] == a)
			c = pre;
		for (; c < cur; ++c)
		{
			vector<int> r = R[c];
			r.push_back(a);
			R.push_back(move(r));
		}
	}
	assert(static_cast<int>(R.size()) == cap);
	return R;
}


int main()
{
	vector<int>
		a = { 1, 2, 2 },
		b = { 2, 2, 2 };
	output(subsetsWithDup(b), "Subsets II");
	output(subsetsWithDup(a), "Subsets II");
}
