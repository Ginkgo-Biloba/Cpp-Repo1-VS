#include "leetcode.hpp"

/* 823. 带因子的二叉树

给出一个含有不重复整数元素的数组，每个整数均大于 1。

我们用这些整数来构建二叉树，每个整数可以使用任意次数。

其中：每个非叶结点的值应等于它的两个子结点的值的乘积。

满足条件的二叉树一共有多少个？返回的结果应模除 10 ** 9 + 7。


示例 1:
输入: A = [2, 4]
输出: 3
解释: 我们可以得到这些二叉树: [2], [4], [4, 2, 2]

示例 2:
输入: A = [2, 4, 5, 10]
输出: 7
解释: 我们可以得到这些二叉树: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].

提示:
	1 <= A.length <= 1000.
	2 <= A[i] <= 10 ^ 9.
*/

int numFactoredBinaryTrees(vector<int>& A)
{
	int64_t const Mod = 1e9 + 7;
	int len = static_cast<int>(A.size());
	vector<int64_t> S(len, 1);

	sort(A.begin(), A.end());
	for (int i = 1; i < len; ++i)
	{
		int L = 0, R = i - 1;
		while (L <= R)
		{
			int64_t p = static_cast<int64_t>(A[L]) * A[R];
			if (p < A[i])
				++L;
			else if (p > A[i])
				--R;
			else
			{
				S[i] = (S[i] + S[L] * S[R] * (1 + (L != R))) % Mod;
				++L;
				--R;
			}
		}
	}
	for (int i = 1; i < len; ++i)
		S[0] = (S[0] + S[i]) % Mod;

	return static_cast<int>(S[0]);
}


int main()
{
	vector<int>
		a = { 2, 4 },
		b = { 2, 4, 5, 10 };
	OutExpr(numFactoredBinaryTrees(a), "%d");
	OutExpr(numFactoredBinaryTrees(b), "%d");
}
