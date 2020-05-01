#include "leetcode.hpp"

/* 1424. 对角线遍历 II

给你一个列表 nums ，里面每一个元素都是一个整数列表。
请你依照下面各图的规则，按顺序返回 nums 中对角线上的整数。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/04/23/sample_1_1784.png
输入：nums = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,4,2,7,5,3,8,6,9]

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/04/23/sample_2_1784.png
输入：nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
输出：[1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]

示例 3：
输入：nums = [[1,2,3],[4],[5,6,7],[8],[9,10,11]]
输出：[1,4,2,5,3,8,6,9,7,10,11]

示例 4：
输入：nums = [[1,2,3,4,5,6]]
输出：[1,2,3,4,5,6]

提示：
	1 <= nums.length <= 10^5
	1 <= nums[i].length <= 10^5
	1 <= nums[i][j] <= 10^9
	nums 中最多有 10^5 个数字。
*/

class Solution
{
public:
	vector<int> findDiagonalOrder_Org(vector<vector<int>>& A)
	{
		vector<int> R;
		vector<pair<int, int>> P;
		int rows = static_cast<int>(A.size());
		for (int h = 0; h < rows; ++h)
		{
			int len = static_cast<int>(A[h].size());
			for (int w = 0; w < len; ++w)
				P.emplace_back(w, h);
		}
		sort(P.begin(), P.end(),
			[](pair<int, int> const& a, pair<int, int> const& b) -> bool
		{
			int c = a.first + a.second;
			int d = b.first + b.second;
			return (c < d) || (c == d && a.first < b.first);
		});
		R.reserve(P.size());
		for (pair<int, int> const& p : P)
			R.push_back(A[p.second][p.first]);
		return R;
	}

	vector<int> findDiagonalOrder(vector<vector<int>>& A)
	{
		int rows = static_cast<int>(A.size());
		vector<int> R;
		vector<pair<int, int>> current, nextfor;
		current.reserve(rows);
		nextfor.reserve(rows);
		current.emplace_back(0, 0);
		while (!current.empty())
		{
			nextfor.clear();
			for (auto const& p : current)
			{
				int h = p.first;
				int w = p.second;
				R.push_back(A[h][w]);
				// 新行
				if (w == 0 && h + 1 < rows)
					nextfor.emplace_back(h + 1, 0);
				// 右边
				if (w + 1 < static_cast<int>(A[h].size()))
					nextfor.emplace_back(h, w + 1);
			}
			nextfor.swap(current);
		}
		return R;
	}
};


int main()
{
	vector<vector<int>>
		a = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } },
		b = { { 1, 2, 3, 4, 5 }, { 6, 7 }, { 8 }, { 9, 10, 11 }, { 12, 13, 14, 15, 16 } },
		c = { { 1, 2, 3 }, { 4 }, { 5, 6, 7 }, { 8 }, { 9, 10, 11 } },
		d = { { 1, 2, 3, 4, 5, 6 } };
	Solution s;
	output(s.findDiagonalOrder(a), "Diagonal Traverse II");
	output(s.findDiagonalOrder(b), "Diagonal Traverse II");
	output(s.findDiagonalOrder(c), "Diagonal Traverse II");
	output(s.findDiagonalOrder(d), "Diagonal Traverse II");
}
