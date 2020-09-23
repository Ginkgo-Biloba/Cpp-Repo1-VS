#include "leetcode.hpp"

/* 1043. 分隔数组以得到最大和

给出整数数组 A，将该数组分隔为长度最多为 K 的几个（连续）子数组。
分隔完成后，每个子数组的中的值都会变为该子数组中的最大值。

返回给定数组完成分隔后的最大和。

示例：
输入：A = [1,15,7,9,2,5,10], K = 3
输出：84
解释：A 变为 [15,15,15,9,10,10,10]

提示：
	1 <= K <= A.length <= 500
	0 <= A[i] <= 10^6
*/


int maxSumAfterPartitioning(vector<int>& A, int K)
{
	int len = static_cast<int>(A.size());
	// dp[i+1] 是 A[0]~A[i] 的答案
	vector<int> dp(len + 1);
	for (int i = 0; i < len; ++i)
	{
		int cur = INT_MIN, val = INT_MIN;
		for (int k = 1; k <= K; ++k)
		{
			int h = i - k + 1;
			if (h < 0)
				break;
			cur = max(cur, A[h]);
			val = max(val, dp[h] + cur * k);
		}
		dp[i + 1] = val;
	}
	return dp[len];
}

int main()
{
	vector<int> a = { 1, 15, 7, 9, 2, 5, 10 };
	OutExpr(maxSumAfterPartitioning(a, 3), "%d");
}
