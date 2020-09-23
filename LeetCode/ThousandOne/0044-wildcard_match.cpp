#include "leetcode.hpp"

/* 44. 通配符匹配

给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。

'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）。

两个字符串完全匹配才算匹配成功。

说明:
	s 可能为空，且只包含从 a-z 的小写字母。
	p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *。

示例 1:
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。

示例 2:
输入:
s = "aa"
p = "*"
输出: true
解释: '*' 可以匹配任意字符串。

示例 3:
输入:
s = "cb"
p = "?a"
输出: false
解释: '?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。

示例 4:
输入:
s = "adceb"
p = "*a*b"
输出: true
解释: 第一个 '*' 可以匹配空字符串, 第二个 '*' 可以匹配字符串 "dce".

示例 5:
输入:
s = "acdcb"
p = "a*c?b"
输入: false
*/

// https://leetcode.com/problems/wildcard-matching/discuss/17810/Linear-runtime-and-constant-space-solution
// 抄的
bool isMatch(char const* s, char const* p)
{
	char const* ast = NULL; /* ast(*) */
	char const* ss = s; /* 字符串 s 中匹配 * 的起始位置 */
	while (*s) /* *s != '\0' */
	{
		/* 当两个字符匹配或者在模式串 p 中发现 ? 时两个指针都前进 */
		/* 注意 *p 不会前行超过长度 */
		if ((*p == '?') || (*p == *s))
		{
			s++;
			p++;
		}

		/* 在模式串中 p 发现 *，跟踪 * 的索引，仅仅前行模式串 */
		else if (*p == '*')
		{
			ast = p;
			p++;
			ss = s;
		}

		/* 当前字符不匹配，最后一个模式是 *，当前模式指针不是 ast */
		/* 仅仅前行模式串指针 */
		else if (ast) /* ast != nullptr */
		{
			p = ast + 1;
			++ss;
			s = ss;
		}

		/* 当前模式不是 *，最后一个模式也不是 *，则字符串不匹配 */
		else
			return false;
	}

	/* 检查模式串中剩余字符 */
	while (*p == '*') p++;

	return !(*p); /* *p == '\0' */
}


int main()
{
	OutBool(isMatch("aa", "a"));
	OutBool(isMatch("aa", "*"));
	OutBool(isMatch("cb", "?a"));
	OutBool(isMatch("adceb", "*a*b"));
	OutBool(isMatch("acdcb", "a*c?b"));
}
