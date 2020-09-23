#include "leetcode.hpp"

/* 691. 贴纸拼词

我们给出了 N 种不同类型的贴纸。每个贴纸上都有一个小写的英文单词。
你希望从自己的贴纸集合中裁剪单个字母并重新排列它们，从而拼写出给定的目标字符串 target。
如果你愿意的话，你可以不止一次地使用每一张贴纸，而且每一张贴纸的数量都是无限的。
拼出目标 target 所需的最小贴纸数量是多少？如果任务不可能，则返回 -1。

示例 1：
输入：
["with", "example", "science"], "thehat"
输出：
3
解释：
我们可以使用 2 个 "with" 贴纸，和 1 个 "example" 贴纸。
把贴纸上的字母剪下来并重新排列后，就可以形成目标 “thehat“ 了。
此外，这是形成目标字符串所需的最小贴纸数量。

示例 2：
输入：
["notice", "possible"], "basicbasic"
输出：
-1
解释：
我们不能通过剪切给定贴纸的字母来形成目标“basicbasic”。

提示：
	stickers 长度范围是 [1, 50]。
	stickers 由小写英文单词组成（不带撇号）。
	target 的长度在 [1, 15] 范围内，由小写字母组成。
	在所有的测试案例中，所有的单词都是从 1000 个最常见的美国英语单词中随机选取的，目标是两个随机单词的串联。
	时间限制可能比平时更具挑战性。预计 50 个贴纸的测试案例平均可在35ms内解决。
*/

// https://leetcode.com/problems/stickers-to-spell-word/discuss/108333/Rewrite-of-contest-winner's-solution
// 抄的
int minStickers(vector<string>& src, string const& dst)
{
	// if target has n chars, there will be m=2^n-1 subset of characters in target
	int n = static_cast<int>(dst.size());
	// use index 0 - 2^n-1 as bitmaps to represent each subset of all chars of target
	int N = 1 << n;
	// first thing we know is : dp[empty set] requires 0 stickers,
	vector<unsigned> dp(N, UINT_MAX);
	dp[0] = 0;
	// for every subset i, start from 00000...(emptyset) to 111111...(the target)
	for (int i = 0; i < N; ++i)
	{
		if (dp[i] == UINT_MAX)
			continue;
		// 多这一个字符串，可以将状态 i 变到状态 sub
		// try use each sticker as an char provider to populate a super-set of i,
		for (string const& s : src)
		{
			int sub = i;
			// to do that, for each char in the sticker,
			for (char c : s)
			{
				// try apply it on a missing char in the subset of target
				for (int r = 0; r < n; ++r)
					if (dst[r] == c && !((sub >> r) & 1))
					{
						sub |= (1 << r);
						break;
					}
				// after you apply all possible chars in a sticker
				// you get an superset that take 1 extra sticker than subset would take
				// so you can try to update the superset's minsticker number with dp[sub]+1;
			}
			dp[sub] = std::min(dp[sub], dp[i] + 1);
		}
	}
	return dp[N - 1];
}


int main()
{
	vector<string> sk1 = { "with", "example", "science" };
	vector<string> sk2 = { "notice", "possible" };
	OutExpr(minStickers(sk1, "thehat"), "%d");
	OutExpr(minStickers(sk2, "basicbasic"), "%d");
}
