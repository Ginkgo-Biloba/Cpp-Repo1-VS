#include "leetcode.hpp"

/* 1005. K 次取反后最大化的数组和

给定一个整数数组 A，我们只能用以下方法修改该数组：
	我们选择某个个索引 i 并将 A[i] 替换为 -A[i]，然后总共重复这个过程 K 次。
	我们可以多次选择同一个索引 i。

以这种方式修改数组后，返回数组可能的最大和。

示例 1：
输入：A = [4,2,3], K = 1
输出：5
解释：选择索引 (1,) ，然后 A 变为 [4,-2,3]。

示例 2：
输入：A = [3,-1,0,2], K = 3
输出：6
解释：选择索引 (1, 2, 2) ，然后 A 变为 [3,1,0,2]。

示例 3：
输入：A = [2,-3,-1,5,-4], K = 2
输出：13
解释：选择索引 (1, 4) ，然后 A 变为 [2,3,-1,5,4]。

提示：
	1 <= A.length <= 10000
	1 <= K <= 10000
	-100 <= A[i] <= 100
*/


// 小顶堆
void adjust(vector<int>& A, int p)
{
	int len = static_cast<int>(A.size());
	int val = A[p];
	int d = p * 2 + 1;
	while (d < len)
	{
		if (d + 1 < len && A[d + 1] < A[d])
			++d;
		if (val <= A[d])
			break;
		A[p] = A[d];
		p = d;
		d = p * 2 + 1;
	}
	A[p] = val;
}

int largestSumAfterKNegations(vector<int>& A, int K)
{
	int len = static_cast<int>(A.size());
	int sum = 0;
	for (int p = len / 2 - 1; p >= 0; --p)
		adjust(A, p);
	for (; K > 0; --K)
	{
		A[0] = -A[0];
		adjust(A, 0);
	}
	for (int i = 0; i < len; ++i)
		sum += A[i];
	return sum;
}


int main()
{
	vector<int>
		a = { 4, 2, 3 },
		b = { 3, -1, 0, 2 },
		c = { 2, -3, -1, 5, -4 };
	OutExpr(largestSumAfterKNegations(a, 1), "%d");
	OutExpr(largestSumAfterKNegations(b, 3), "%d");
	OutExpr(largestSumAfterKNegations(c, 2), "%d");
}
