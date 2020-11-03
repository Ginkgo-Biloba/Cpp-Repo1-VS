#include "leetcode.hpp"

/* 1639. 通过给定词典构造目标字符串的方案数

给你一个字符串列表 words 和一个目标字符串 target 。words 中所有字符串都 长度相同  。

你的目标是使用给定的 words 字符串列表按照下述规则构造 target ：
	从左到右依次构造 target 的每一个字符。
	为了得到 target 第 i 个字符（下标从 0 开始），当 target[i] = words[j][k] 时，你可以使用 words 列表中第 j 个字符串的第 k 个字符。
	一旦你使用了 words 中第 j 个字符串的第 k 个字符，你不能再使用 words 字符串列表中任意单词的第 x 个字符（x <= k）。也就是说，所有单词下标小于等于 k 的字符都不能再被使用。
	请你重复此过程直到得到目标字符串 target 。

请注意， 在构造目标字符串的过程中，你可以按照上述规定使用 words 列表中 同一个字符串 的 多个字符 。

请你返回使用 words 构造 target 的方案数。由于答案可能会很大，请对 109 + 7 取余 后返回。

（译者注：此题目求的是有多少个不同的 k 序列，详情请见示例。）

示例 1：
输入：words = ["acca","bbbb","caca"], target = "aba"
输出：6
解释：总共有 6 种方法构造目标串。
"aba" -> 下标为 0 ("acca")，下标为 1 ("bbbb")，下标为 3 ("caca")
"aba" -> 下标为 0 ("acca")，下标为 2 ("bbbb")，下标为 3 ("caca")
"aba" -> 下标为 0 ("acca")，下标为 1 ("bbbb")，下标为 3 ("acca")
"aba" -> 下标为 0 ("acca")，下标为 2 ("bbbb")，下标为 3 ("acca")
"aba" -> 下标为 1 ("caca")，下标为 2 ("bbbb")，下标为 3 ("acca")
"aba" -> 下标为 1 ("caca")，下标为 2 ("bbbb")，下标为 3 ("caca")

示例 2：
输入：words = ["abba","baab"], target = "bab"
输出：4
解释：总共有 4 种不同形成 target 的方法。
"bab" -> 下标为 0 ("baab")，下标为 1 ("baab")，下标为 2 ("abba")
"bab" -> 下标为 0 ("baab")，下标为 1 ("baab")，下标为 3 ("baab")
"bab" -> 下标为 0 ("baab")，下标为 2 ("baab")，下标为 3 ("baab")
"bab" -> 下标为 1 ("abba")，下标为 2 ("baab")，下标为 3 ("baab")

示例 3：
输入：words = ["abcd"], target = "abcd"
输出：1

示例 4：
输入：words = ["abab","baba","abba","baab"], target = "abba"
输出：16

提示：
	1 <= words.length <= 1000
	1 <= words[i].length <= 1000
	words 中所有单词长度相同。
	1 <= target.length <= 1000
	words[i] 和 target 都仅包含小写英文字母。
*/

// https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/discuss/917779/JavaC%2B%2BPython-Space-O(N)
// 抄的
int numWays(vector<string>& words, string target)
{
	int64_t const mod = 1e9 + 7;
	int m = static_cast<int>(words.size());
	int n = static_cast<int>(words[0].size());
	int k = static_cast<int>(target.size());
	vector<int64_t> dp(k + 1);
	int64_t C[128];
	dp[0] = 1;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 'a'; j <= 'z'; ++j)
			C[j] = 0;
		for (int j = 0; j < m; ++j)
			++(C[words[j][i]]);
		// 从后往前，直接覆盖
		for (int j = k - 1; j >= 0; --j)
			dp[j + 1] = (dp[j + 1] + dp[j] * C[target[j]]) % mod;
	}
	return static_cast<int>(dp[k]);
}


int main()
{
	vector<string>
		a = { "acca", "bbbb", "caca" },
		b = { "abba", "baab" },
		c = { "abcd" },
		d = { "abab", "baba", "abba", "baab" };
	OutExpr(numWays(a, "aba"), "%d");
	OutExpr(numWays(b, "bab"), "%d");
	OutExpr(numWays(c, "abcd"), "%d");
	OutExpr(numWays(d, "abba"), "%d");
}
