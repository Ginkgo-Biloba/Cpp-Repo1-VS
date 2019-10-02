#include "leetcode.hpp"

/* 564. 寻找最近的回文数

给定一个整数 n ，你需要找到与它最近的回文数（不包括自身）。
“最近的”定义为两个整数差的绝对值最小。

示例 1:
输入: "123"
输出: "121"

注意:
	n 是由字符串表示的正整数，其长度不超过18。
	如果有多个结果，返回最小的那个。
*/

// https://leetcode.com/problems/find-the-closest-palindrome/discuss/102396/C%2B%2B-short-solution-only-need-to-compare-5-numbers
// 抄的
string nearestPalindromic(string n)
{
	typedef long long llong;
	int len = static_cast<int>(n.size());
	vector<llong> cand;
	cand.reserve(6);
	cand.push_back(std::pow(10, len) + 1);
	cand.push_back(std::pow(10, len - 1) - 1);
	llong prefix = std::stoll(n.substr(0, (len + 1) / 2));
	for (llong d = -1; d <= 1; ++d)
	{
		string p = std::to_string(prefix + d);
		string pp = p + string(p.rbegin() + (len & 1), p.rend());
		cand.push_back(std::stoll(pp));
	}
	llong N = std::stoll(n), mindiff = LLONG_MAX, ans = N;
	for (llong val : cand)
	{
		llong d = std::abs(val - N);
		if (val == N)
			;
		else if (d < mindiff)
		{
			mindiff = d;
			ans = val;
		}
		else if (d == mindiff)
			ans = std::min(ans, val);
	}
	return std::to_string(ans);
}


int main()
{
	OutExpr(nearestPalindromic("123").c_str(), "%s");
}
