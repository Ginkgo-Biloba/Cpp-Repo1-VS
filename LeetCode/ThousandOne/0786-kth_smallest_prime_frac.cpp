#include "leetcode.hpp"

/* 786. 第 K 个最小的素数分数

一个已排序好的表 A，其包含 1 和其他一些素数.当列表中的每一个 p<q 时，我们可以构造一个分数 p/q 。

那么第 n 个最小的分数是多少呢?
以整数数组的形式返回你的答案, 这里 answer[0] = p 且 answer[1] = q.

示例:
输入: A = [1, 2, 3, 5], K = 3
输出: [2, 5]
解释:
已构造好的分数,排序后如下所示:
1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
很明显第三个最小的分数是 2/5.

输入: A = [1, 7], K = 1
输出: [1, 7]

注意:
	A 的取值范围在 2 — 2000.
	每个 A[i] 的值在 1 —30000.
	K 取值范围为 1 —A.length * (A.length - 1) / 2
*/

struct VLR
{
	double v;
	int l, r;
	bool operator<(VLR const& rhs) const
	{
		return v < rhs.v;
	}
};

vector<int> kthSmallestPrimeFraction1(vector<int>& A, int K)
{
	vector<int> ans(2);
	priority_queue<VLR> q;
	VLR cur;
	cur.l = 0;
	cur.r = static_cast<int>(A.size()) - 1;
	for (; cur.l < cur.r; ++(cur.l))
	{
		cur.v = -1.0 * A[cur.l] / A[cur.r];
		q.push(cur);
	}
	while (--K)
	{
		cur = q.top();
		q.pop();
		// printf("[%d, %d] -> (%d / %d) -> %f\n",
			// cur.l, cur.r, A[cur.l], A[cur.r], -cur.v);
		--(cur.r);
		if (cur.l < cur.r)
		{
			cur.v = -1.0 * A[cur.l] / A[cur.r];
			q.push(cur);
		}
	}

	ans[0] = A[q.top().l];
	ans[1] = A[q.top().r];
	return ans;
}

// https://leetcode.com/problems/n-th-smallest-prime-fraction/discuss/115819/Summary-of-solutions-for-problems-%22reducible%22-to-LeetCode-378
vector<int> kthSmallestPrimeFraction(vector<int>& A, int K)
{
	double L = 0, R = 1;
	int p = 0, q = 1;
	vector<int> ans(2);
	int len = static_cast<int>(A.size());

	while (L < R)
	{
		double M = (L + R) * 0.5;
		int cnt = 0, i = 0, n = 1;
		p = A[0], q = A[len - 1];
		for (; n < len; ++n)
		{
			while (i < n && A[i] <= M * A[n])
				++i;
			cnt += i;
			if ((i > 0) && (p * A[n] < q * A[i - 1]))
			{
				p = A[i - 1];
				q = A[n];
				// printf("[%d, %d] -> (%d / %d) -> %f\n",
					// i, n, p, q, 1.0 * p / q);
			}
		}
		// printf("cnt = %d\n", cnt);
		if (cnt < K)
			L = M;
		else if (cnt > K)
			R = M;
		else
			break;
	}

	ans[0] = p;
	ans[1] = q;
	return ans;
}

int main()
{
	vector<int>
		A0 = { 1, 2, 3, 5 },
		A1 = { 1, 7, 23, 29, 47 },
		A2 = { 1, 13, 17, 59 };
	output(kthSmallestPrimeFraction(A0, 3), "kthSmallestPrimeFraction");
	output(kthSmallestPrimeFraction(A1, 8), "kthSmallestPrimeFraction");
	output(kthSmallestPrimeFraction(A2, 6), "kthSmallestPrimeFraction");
}
