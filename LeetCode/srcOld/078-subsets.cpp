#include "leetcode.hpp"

/* 78. 子集

给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

说明：解集不能包含重复的子集。

示例:

输入: nums = [1,2,3]
输出:
[
	[3],
	[1],
	[2],
	[1,2,3],
	[1,3],
	[2,3],
	[1,2],
	[]
]
*/

vector<vector<int>> subsets(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	vector<int> mask(len + 1);
	vector<vector<int>> R;
	vector<int> r;
	for (int i = 0; i <= len; ++i)
		mask[i] = 1 << i;
	for (int i = 0; i < mask[len]; ++i)
	{
		r.reserve(__builtin_popcount(i));
		for (int b = 0; b < len; ++b)
		{
			if (i & mask[b])
				r.push_back(A[b]);
		}
		R.push_back(move(r));
	}
	return R;
}


int main()
{
	vector<int> a = { 1, 2, 3 };
	output(subsets(a), "Subsets");
}
