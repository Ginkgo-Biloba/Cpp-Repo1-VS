#include "leetcode.hpp"

/* 1478. 安排邮筒

给你一个房屋数组houses 和一个整数 k ，其中 houses[i] 是第 i 栋房子在一条街上的位置，现需要在这条街上安排 k 个邮筒。

请你返回每栋房子与离它最近的邮筒之间的距离的 最小 总和。

答案保证在 32 位有符号整数范围以内。

示例 1：
https://assets.leetcode.com/uploads/2020/05/07/sample_11_1816.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/06/13/sample_11_1816.png
输入：houses = [1,4,8,10,20], k = 3
输出：5
解释：将邮筒分别安放在位置 3， 9 和 20 处。
每个房子到最近邮筒的距离和为 |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5 。

示例 2：
https://assets.leetcode.com/uploads/2020/05/07/sample_2_1816.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/06/13/sample_2_1816.png
输入：houses = [2,3,5,12,18], k = 2
输出：9
解释：将邮筒分别安放在位置 3 和 14 处。
每个房子到最近邮筒距离和为 |2-3| + |3-3| + |5-3| + |12-14| + |18-14| = 9 。

示例 3：
输入：houses = [7,4,6,1], k = 1
输出：8

示例 4：
输入：houses = [3,6,14,10], k = 4
输出：0

提示：
	n == houses.length
	1 <= n <= 100
	1 <= houses[i] <= 10^4
	1 <= k <= n
	数组 houses 中的整数互不相同。
*/

// https://leetcode.com/problems/allocate-mailboxes/discuss/685403/JavaC%2B%2BPython-DP-Solution
// 抄的
int minDistance(vector<int>& A, int K)
{
	int const inf = 1e9 + 7;
	int n = static_cast<int>(A.size());
	vector<int> B(n + 1), dp(n, inf);
	sort(A.begin(), A.end());
	for (int i = 0; i < n; ++i)
		B[i + 1] = B[i] + A[i];
	for (int k = 1; k <= K; ++k)
		for (int i = n - 1; i > k - 2; --i)
			for (int h = k - 2; h < i; ++h)
			{
				int m1 = (h + i + 1) / 2, m2 = (h + i + 2) / 2;
				int last = (B[i + 1] - B[m2]) - (B[m1 + 1] - B[h + 1]);
				last += (h >= 0) ? dp[h] : 0;
				dp[i] = min(dp[i], last);
			}
	return dp[n - 1];
}


int main()
{
	vector<int>
		a = { 1, 4, 8, 10, 20 },
		b = { 2, 3, 5, 12, 18 },
		c = { 7, 4, 6, 1 },
		d = { 3, 6, 14, 10 };
	OutExpr(minDistance(a, 3), "%d");
	OutExpr(minDistance(b, 2), "%d");
	OutExpr(minDistance(c, 1), "%d");
	OutExpr(minDistance(d, 4), "%d");
}
