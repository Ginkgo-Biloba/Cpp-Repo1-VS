#include "leetcode.hpp"

/* 440. 字典序的第K小数字
给定整数 n 和 k，找到 1 到 n 中字典序第 k 小的数字。
注意：1 ≤ k ≤ n ≤ 109。

示例 :
输入:
n: 13   k: 2
输出:
10
解释:
字典序的排列是 [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9]，所以第二小的数字是 10。
*/

// https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/discuss/92254/C%2B%2BPython-0ms-O((log-n)2)-time-O(1)-space-super-easy-solution-with-detailed-explanations
// 抄的
int findKthNumber(int n, int k)
{
	int ans = 1;
	for (--k; k > 0;)
	{
		// 计算以 ans* 为前缀的数字个数
		int count = 0;
		for (int64_t left = ans, right = left + 1;
			left <= n;
			left *= 10, right *= 10)
		{
			count += static_cast<int>(
				std::min(n + INT64_C(1), right) - left);
		}

		// 跳过 ans*
		if (count <= k)
		{
			++ans;
			k -= count;
		}
		else
		{
			ans *= 10;
			--k;
		}
	}

	return ans;
}


int main()
{
	OutExpr(findKthNumber(13, 2), "%d");
}
