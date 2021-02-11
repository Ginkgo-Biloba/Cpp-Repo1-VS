#include "leetcode.hpp"

/* 1737. 满足三条件之一需改变的最少字符数

给你两个字符串 a 和 b ，二者均由小写字母组成。
一步操作中，你可以将 a 或 b 中的 任一字符 改变为 任一小写字母 。

操作的最终目标是满足下列三个条件 之一 ：
	a 中的 每个字母 在字母表中 严格小于 b 中的 每个字母 。
	b 中的 每个字母 在字母表中 严格小于 a 中的 每个字母 。
	a 和 b 都 由 同一个 字母组成。

返回达成目标所需的 最少 操作数。

示例 1：
输入：a = "aba", b = "caa"
输出：2
解释：满足每个条件的最佳方案分别是：
1) 将 b 变为 "ccc"，2 次操作，满足 a 中的每个字母都小于 b 中的每个字母；
2) 将 a 变为 "bbb" 并将 b 变为 "aaa"，3 次操作，满足 b 中的每个字母都小于 a 中的每个字母；
3) 将 a 变为 "aaa" 并将 b 变为 "aaa"，2 次操作，满足 a 和 b 由同一个字母组成。
最佳的方案只需要 2 次操作（满足条件 1 或者条件 3）。

示例 2：
输入：a = "dabadd", b = "cda"
输出：3
解释：满足条件 1 的最佳方案是将 b 变为 "eee" 。

提示：
	1 <= a.length, b.length <= 10^5
	a 和 b 只由小写字母组成
*/

int check(string const& a, string const& b, int c)
{
	int s = 0;
	for (int i : a)
		s += (i >= c);
	for (int i : b)
		s += (i < c);
	return s;
}

int minCharacters(string a, string b)
{
	int ca[128] = { 0 }, cb[128] = { 0 };
	for (int i : a)
		ca[i] += 1;
	for (int i : b)
		cb[i] += 1;
	int op1 = INT_MAX, op2 = op1;
	int op3 = ca['a'] + cb['a'];
	for (int i = 'b'; i <= 'z'; ++i)
	{
		op1 = min(op1, check(a, b, i));
		op2 = min(op2, check(b, a, i));
		op3 = max(op3, ca[i] + cb[i]);
	}
	op3 = -op3
		+ static_cast<int>(a.size())
		+ static_cast<int>(b.size());
	return min(min(op1, op2), op3);
}


int main()
{
	OutExpr(minCharacters("aba", "caa"), "%d");
	OutExpr(minCharacters("dabadd", "cda"), "%d");
}
