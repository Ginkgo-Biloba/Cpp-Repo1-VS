#include "leetcode.hpp"

/* 816. 模糊坐标

我们有一些二维坐标，如 "(1, 3)" 或 "(2, 0.5)"，然后我们移除所有逗号，小数点和空格，得到一个字符串S。
返回所有可能的原始字符串到一个列表中。

原始的坐标表示法不会存在多余的零，所以不会出现类似于"00", "0.0", "0.00", "1.0", "001", "00.01"或一些其他更小的数来表示坐标。
此外，一个小数点前至少存在一个数，所以也不会出现“.1”形式的数字。

最后返回的列表可以是任意顺序的。而且注意返回的两个数字中间（逗号之后）都有一个空格。

示例 1:
输入: "(123)"
输出: ["(1, 23)", "(12, 3)", "(1.2, 3)", "(1, 2.3)"]

示例 2:
输入: "(00011)"
输出:  ["(0.001, 1)", "(0, 0.011)"]
解释:
0.0, 00, 0001 或 00.01 是不被允许的。

示例 3:
输入: "(0123)"
输出: ["(0, 123)", "(0, 12.3)", "(0, 1.23)", "(0.1, 23)", "(0.1, 2.3)", "(0.12, 3)"]

示例 4:
输入: "(100)"
输出: [(10, 0)]
解释:
1.0 是不被允许的。

提示:
	4 <= S.length <= 12.
	S[0] = "(", S[S.length - 1] = ")", 且字符串 S 中的其他元素都是数字。
*/

// https://leetcode.com/problems/ambiguous-coordinates/discuss/123881/Concise-C%2B%2B-solution-with-comments
// 抄的
vector<string> make(string const& s)
{
	vector<string> ans;
	if (s.size() == 1)
	{
		ans.push_back(s);
		return ans;
	}
	if (s.front() == '0') // 0xxx
	{
		if (s.back() == '0') // 0xxx0
			return ans;
		ans.push_back("0." + s.substr(1)); // 0xxx9
		return ans;
	}
	if (s.back() == '0') // 9xxx0
	{
		ans.push_back(s);
		return ans;
	}

	size_t i = 1, len = s.size();
	ans.push_back(s); // 9xxx9
	for (; i < len; ++i)
		ans.push_back(s.substr(0, i) + "." + s.substr(i));
	return ans;
}

vector<string> ambiguousCoordinates(string S)
{
	char buf[32];
	vector<string> ans;
	size_t i = 2, len = S.size(); // positon of comma
	for (; i < len - 1; ++i)
	{
		vector<string> L = make(S.substr(1, i - 1));
		if (L.empty())
			continue;
		vector<string> R = make(S.substr(i, len - i - 1));
		if (R.empty())
			continue;
		for (string const& x : L)
			for (string const& y : R)
			{
				sprintf(buf, "(%s, %s)", x.c_str(), y.c_str());
				ans.emplace_back(buf);
			}
	}
	return ans;
}


int main()
{
	output(ambiguousCoordinates("(123)"), " \t", "Ambiguous Coordinates");
	output(ambiguousCoordinates("(00011)"), " \t", "Ambiguous Coordinates");
	output(ambiguousCoordinates("(0123)"), " \t", "Ambiguous Coordinates");
	output(ambiguousCoordinates("(100)"), " \t", "Ambiguous Coordinates");
}
