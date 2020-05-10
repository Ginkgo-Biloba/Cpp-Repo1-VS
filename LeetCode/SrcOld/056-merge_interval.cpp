#include "leetcode.hpp"

/* 56. 合并区间

给出一个区间的集合，请合并所有重叠的区间。

示例 1:
输入: [[1,3],[2,6],[8,10],[15,18]]
输出: [[1,6],[8,10],[15,18]]
解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例 2:
输入: [[1,4],[4,5]]
输出: [[1,5]]
解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。
*/

vector<vector<int>> merge(vector<vector<int>>& A)
{
	vector<vector<int>> R;
	vector<int> r(2);
	int len = static_cast<int>(A.size());
	sort(A.begin(), A.end(),
		[](vector<int> const& a, vector<int> const& b)
	{
		return (a[0] < b[0]) || (a[0] == b[0] && a[1] > b[1]);
	});
	for (int i = 0; i < len;)
	{
		int k = i + 1;
		r[0] = A[i][0];
		r[1] = A[i][1];
		while ((k < len) && (A[k][0] <= r[1]))
		{
			r[1] = max(r[1], A[k][1]);
			++k;
		}
		R.push_back(r);
		i = k;
	}
	return R;
}


int main()
{
	vector<vector<int>>
		a = { { 1, 3 }, { 2, 6 }, { 8, 10 }, { 15, 18 } },
		b = { { 1, 4 }, { 4, 5 } };
	output(merge(a), "Merge Intervals");
	output(merge(b), "Merge Intervals");
}
