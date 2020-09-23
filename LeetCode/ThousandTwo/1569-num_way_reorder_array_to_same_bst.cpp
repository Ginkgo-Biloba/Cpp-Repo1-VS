#include "leetcode.hpp"

/* 1569. 将子数组重新排序得到同一个二叉查找树的方案数

给你一个数组 nums 表示 1 到 n 的一个排列。
我们按照元素在 nums 中的顺序依次插入一个初始为空的二叉查找树（BST）。
请你统计将 nums 重新排序后，统计满足如下条件的方案数：重排后得到的二叉查找树与 nums 原本数字顺序得到的二叉查找树相同。

比方说，给你 nums = [2,1,3]，我们得到一棵 2 为根，1 为左孩子，3 为右孩子的树。
数组 [2,3,1] 也能得到相同的 BST，但 [3,2,1] 会得到一棵不同的 BST 。

请你返回重排 nums 后，与原数组 nums 得到相同二叉查找树的方案数。

由于答案可能会很大，请将结果对 10^9 + 7 取余数。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/30/bb.png
https://assets.leetcode.com/uploads/2020/08/12/bb.png
输入：nums = [2,1,3]
输出：1
解释：我们将 nums 重排， [2,3,1] 能得到相同的 BST 。
没有其他得到相同 BST 的方案了。

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/30/ex1.png
https://assets.leetcode.com/uploads/2020/08/12/ex1.png
输入：nums = [3,4,5,1,2]
输出：5
解释：下面 5 个数组会得到相同的 BST：
[3,1,2,4,5]
[3,1,4,2,5]
[3,1,4,5,2]
[3,4,1,2,5]
[3,4,1,5,2]

示例 3：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/30/ex4.png
https://assets.leetcode.com/uploads/2020/08/12/ex4.png
输入：nums = [1,2,3]
输出：0
解释：没有别的排列顺序能得到相同的 BST 。

示例 4：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/08/30/abc.png
https://assets.leetcode.com/uploads/2020/08/12/abc.png
输入：nums = [3,1,2,5,4,6]
输出：19

示例 5：
输入：nums = [9,4,2,1,3,6,5,7,8,14,11,10,12,13,16,15,17,18]
输出：216212978
解释：得到相同 BST 的方案数是 3216212999。将它对 10^9 + 7 取余后得到 216212978。

提示：
	1 <= nums.length <= 1000
	1 <= nums[i] <= nums.length
	nums 中所有数 互不相同 。
*/

class Solution
{
	int C[1000][500];
	vector<int> X, Z;

	int count(int L, int R)
	{
		int64_t const mod = 1e9 + 7;
		int n = R - L;
		if (n < 3)
			return 1;

		int k = 0;
		int a = L + 1, b = a;
		for (; b < R; ++b)
		{
			if (X[b] < X[L])
				X[a++] = X[b];
			else
				Z[k++] = X[b];
		}
		for (b = a; b < R; ++b)
			X[b] = Z[b - a];
		k = min(k, n - 1 - k);
		int64_t cl = count(L + 1, a);
		int64_t cr = count(a, R);
		int64_t lr = C[n - 1][k];
		int64_t all = (cl * cr % mod) * lr % mod;
		return static_cast<int>(all);
	}

public:
	Solution()
	{
		int const mod = 1e9 + 7;
		memset(C, 0, sizeof(C));
		C[0][0] = 1;
		for (int n = 1; n < 1000; ++n)
		{
			C[n][0] = 1;
			for (int k = 1; k < 500; ++k)
				C[n][k] = (C[n - 1][k - 1] + C[n - 1][k]) % mod;
		}
	}

	int numOfWays(vector<int>& nums)
	{
		int const mod = 1e9 + 7;
		Z = X = nums;
		int len = static_cast<int>(X.size());
		int all = count(0, len);
		return (all + mod - 1) % mod;
	}
};


int main()
{
	vector<int>
		a = { 2, 1, 3 },
		b = { 3, 4, 5, 1, 2 },
		c = { 1, 2, 3 },
		d = { 3, 1, 2, 5, 4, 6 },
		e = { 9, 4, 2, 1, 3, 6, 5, 7, 8, 14, 11, 10, 12, 13, 16, 15, 17, 18 },
		f = { 6, 9, 11, 15, 1, 12, 3, 2, 7, 8, 14, 4, 5, 13, 10 },
		g = { 5, 1, 4, 2, 3 };
	Solution s;
	OutExpr(s.numOfWays(a), "%d");
	OutExpr(s.numOfWays(b), "%d");
	OutExpr(s.numOfWays(c), "%d");
	OutExpr(s.numOfWays(d), "%d");
	OutExpr(s.numOfWays(e), "%d");
	OutExpr(s.numOfWays(f), "%d");
	OutExpr(s.numOfWays(g), "%d");
}
