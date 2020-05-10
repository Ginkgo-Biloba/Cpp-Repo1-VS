#include "leetcode.hpp"

/* 57. 插入区间

给出一个无重叠的 ，按照区间起始端点排序的区间列表。

在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。

示例 1:
输入: intervals = [[1,3],[6,9]], newInterval = [2,5]
输出: [[1,5],[6,9]]

示例 2:
输入: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出: [[1,2],[3,10],[12,16]]
解释: 这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10] 重叠。
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

vector<vector<int>> insert_Org(vector<vector<int>>& A, vector<int>& b)
{
	A.push_back(b);
	return merge(A);
}

vector<vector<int>> insert(vector<vector<int>>& A, vector<int>& b)
{
	vector<vector<int>> R;
	int len = static_cast<int>(A.size());
	int i = 0;
	while ((i < len) && A[i][1] < b[0])
	{
		R.push_back(A[i]);
		++i;
	}
	while ((i < len) && A[i][0] <= b[1])
	{
		b[0] = min(b[0], A[i][0]);
		b[1] = max(b[1], A[i][1]);
		++i;
	}
	R.push_back(b);
	while (i < len)
	{
		R.push_back(A[i]);
		++i;
	}
	return R;
}


int main()
{
	vector<vector<int>>
		a = { { 1, 3 }, { 6, 9 } },
		c = { { 1, 2 }, { 3, 5 }, { 6, 7 }, { 8, 10 }, { 12, 16 } };
	vector<int>
		b = { 2, 5 },
		d = { 4, 8 };
	output(insert(a, b), "Insert Interval");
	output(insert(c, d), "Insert Interval");
}
