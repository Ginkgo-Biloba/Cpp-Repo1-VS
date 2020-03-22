#include "leetcode.hpp"

/* 1092. 最短公共超序列

给出两个字符串 str1 和 str2，返回同时以 str1 和 str2 作为子序列的最短字符串。如果答案不止一个，则可以返回满足条件的任意一个答案。

（如果从字符串 T 中删除一些字符（也可能不删除，并且选出的这些字符可以位于 T 中的 任意位置），可以得到字符串 S，那么 S 就是 T 的子序列）

示例：
输入：str1 = "abac", str2 = "cab"
输出："cabac"
解释：
str1 = "abac" 是 "cabac" 的一个子串，因为我们可以删去 "cabac" 的第一个 "c"得到 "abac"。
str2 = "cab" 是 "cabac" 的一个子串，因为我们可以删去 "cabac" 末尾的 "ac" 得到 "cab"。
最终我们给出的答案是满足上述属性的最短字符串。

提示：
	1 <= str1.length, str2.length <= 1000
	str1 和 str2 都由小写英文字母组成
*/

// https://leetcode.com/problems/shortest-common-supersequence/discuss/312702/Java-DP-Solution(Similiar-to-LCS)
// 构建字符串是抄的
string shortestCommonSupersequence(string A, string B)
{
	string C;
	int i, a = static_cast<int>(A.size());
	int k, b = static_cast<int>(B.size());
	vector<int> buf((a + 1) * (b + 1));
	auto dp = [b, &buf](int ia, int ib)
		-> int& { return buf[ia * (b + 1) + ib]; };

	for (i = 1; i <= a; ++i)
		for (k = 1; k <= b; ++k)
		{
			if (A[i - 1] == B[k - 1])
				dp(i, k) = dp(i - 1, k - 1) + 1;
			else
				dp(i, k) = max(dp(i - 1, k), dp(i, k - 1));
		}

	i = a;
	k = b;
	C.reserve(a + b - buf.back());
	while (i > 0 && k > 0)
	{
		if (dp(i, k) == dp(i - 1, k))
		{
			--i;
			C.push_back(A[i]);
		}
		else if (dp(i, k) == dp(i, k - 1))
		{
			--k;
			C.push_back(B[k]);
		}
		else
		{
			--i;
			--k;
			C.push_back(A[i]); // or B[k]
		}
	}
	for (; i > 0; --i)
		C.push_back(A[i - 1]);
	for (; k > 0; --k)
		C.push_back(B[k - 1]);

	reverse(C.begin(), C.end());
	return C;
}


int main()
{
	OutString(shortestCommonSupersequence("abca", "cab"));
}
