#include "leetcode.hpp"

/* 1388. 3n 块披萨

给你一个披萨，它由 3n 块不同大小的部分组成，现在你和你的朋友们需要按照如下规则来分披萨：
	你挑选 任意 一块披萨。
	Alice 将会挑选你所选择的披萨逆时针方向的下一块披萨。
	Bob 将会挑选你所选择的披萨顺时针方向的下一块披萨。
	重复上述过程直到没有披萨剩下。

每一块披萨的大小按顺时针方向由循环数组 slices 表示。

请你返回你可以获得的披萨大小总和的最大值。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/03/21/sample_3_1723.png
输入：slices = [1,2,3,4,5,6]
输出：10
解释：选择大小为 4 的披萨，Alice 和 Bob 分别挑选大小为 3 和 5 的披萨。然后你选择大小为 6 的披萨，Alice 和 Bob 分别挑选大小为 2 和 1 的披萨。你获得的披萨总大小为 4 + 6 = 10 。

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/03/21/sample_4_1723.png
输入：slices = [8,9,8,6,1,1]
输出：16
解释：两轮都选大小为 8 的披萨。
如果你选择大小为 9 的披萨，你的朋友们就会选择大小为 8 的披萨，这种情况下你的总和不是最大的。

示例 3：
输入：slices = [4,1,2,5,8,3,1,9,7]
输出：21

示例 4：
输入：slices = [3,1,2]
输出：3

提示：
	1 <= slices.length <= 500
	slices.length % 3 == 0
	1 <= slices[i] <= 1000
*/

// https://leetcode.com/problems/pizza-with-3n-slices/discuss/546442/PythonC%2B%2B-O(n)-space-Easy-DP-with-explanation
// 抄的
class Solution
{
	vector<int> buf;
	int step;

	int& dp(int y, int x)
	{
		return buf[y * step + x];
	}

	int linear(int* A, int len, int n)
	{
		memset(buf.data(), 0xff, buf.size() * sizeof(buf[0]));
		int ans = INT_MIN;
		for (int i = 0; i < len + 2; ++i)
			dp(i, 0) = 0;
		for (int i = 2; i < len + 2; ++i)
		{
			for (int k = 1; k <= n; ++k)
				dp(i, k) = max(dp(i - 1, k), dp(i - 2, k - 1) + A[i - 2]);
			ans = max(ans, dp(i, n));
		}
		return ans;
	}

public:
	int maxSizeSlices(vector<int>& slices)
	{
		int len = static_cast<int>(slices.size());
		step = len / 3 + 1;
		buf.resize((len + 2) * (len + 2));
		int x = linear(slices.data() + 0, len - 1, len / 3);
		int y = linear(slices.data() + 1, len - 1, len / 3);
		return max(x, y);
	}
};


int main()
{
	vector<int>
		a = { 1, 2, 3, 4, 5, 6 },
		b = { 8, 9, 8, 6, 1, 1 },
		c = { 4, 1, 2, 5, 8, 3, 1, 9, 7 },
		d = { 3, 1, 2 };
	Solution s;
	OutExpr(s.maxSizeSlices(a), "%d");
	OutExpr(s.maxSizeSlices(b), "%d");
	OutExpr(s.maxSizeSlices(c), "%d");
	OutExpr(s.maxSizeSlices(d), "%d");
}
