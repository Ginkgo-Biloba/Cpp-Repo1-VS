#include "leetcode.hpp"

/* 862. 和至少为 K 的最短子数组

返回 A 的最短的非空连续子数组的长度，该子数组的和至少为 K 。

如果没有和至少为 K 的非空子数组，返回 -1。

示例 1：
输入：A = [1], K = 1
输出：1

示例 2：
输入：A = [1,2], K = 4
输出：-1

示例 3：
输入：A = [2,-1,2], K = 3
输出：3

提示：
	1 <= A.length <= 50000
	-10 ^ 5 <= A[i] <= 10 ^ 5
	1 <= K <= 10 ^ 9
*/

// https://leetcode-cn.com/problems/shortest-subarray-with-sum-at-least-k/solution/he-zhi-shao-wei-k-de-zui-duan-zi-shu-zu-by-leetcod/
// https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/discuss/143726/C++JavaPython-O(N)-Using-Deque/150644
// 抄的
int shortestSubarray(vector<int>& A, int K)
{
	int len = static_cast<int>(A.size());
	vector<int64_t> P(A.size() + 1);
	for (int i = 0; i < len; ++i)
		P[i + 1] = P[i] + A[i];

	std::deque<int> q;
	int ans = len + 1;
	for (int i = 1; i <= len; ++i)
	{
		while (!q.empty() && P[i] <= P[q.back()])
			q.pop_back();
		while (!q.empty() && P[i] >= P[q.front()] + K)
		{
			ans = std::min(ans, i - q.front());
			q.pop_front();
		}
		q.push_back(0);
	}
	return ans > len ? -1 : ans;
}


int main()
{
	vector<int>
		a = { 1 },
		b = { 1, 2 },
		c = { 2, -1, 2 };
	OutExpr(shortestSubarray(a, 1), "%d");
	OutExpr(shortestSubarray(b, 4), "%d");
	OutExpr(shortestSubarray(c, 3), "%d");
}
