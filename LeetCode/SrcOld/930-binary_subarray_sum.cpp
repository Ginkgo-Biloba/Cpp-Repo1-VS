#include "leetcode.hpp"

/* 930. 和相同的二元子数组

在由若干 0 和 1  组成的数组 A 中，有多少个和为 S 的非空子数组。

示例：
输入：A = [1,0,1,0,1], S = 2
输出：4
解释：
如下面黑体所示，有 4 个满足题目要求的子数组：
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]

提示：
	A.length <= 30000
	0 <= S <= A.length
	A[i] 为 0 或 1
*/

int atMost(vector<int>& A, int S)
{
	int len = static_cast<int>(A.size());
	int L = 0, R = 0, n = 0;
	for (; R < len; ++R)
	{
		S -= A[R];
		for (; L <= R && S < 0; ++L)
			S += A[L];
		n += R - L + 1;
	}
	return n;
}

int numSubarraysWithSum(vector<int>& A, int S)
{
	return atMost(A, S) - atMost(A, S - 1);
}


int main()
{
	vector<int>
		a = { 1, 0, 1, 0, 1 },
		b = { 0, 0, 0, 0, 0 };
	OutExpr(numSubarraysWithSum(a, 2), "%d");
	OutExpr(numSubarraysWithSum(b, 0), "%d");
}
