#include "leetcode.hpp"

/* 1360. 日期之间隔几天

请你编写一个程序来计算两个日期之间隔了多少天。

日期以字符串形式给出，格式为 YYYY-MM-DD，如示例所示。

示例 1：
输入：date1 = "2019-06-29", date2 = "2019-06-30"
输出：1

示例 2：
输入：date1 = "2020-01-15", date2 = "2019-12-31"
输出：15

提示：
	给定的日期是 1971 年到 2100 年之间的有效日期。
*/

bool isLeap(int y)
{
	return (y % 400 == 0) || (y % 100 != 0 && y % 4 == 0);
}

int from1971(int y, int m, int d)
{
	int const days[13] = { 0,
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int sum = 0;
	for (int i = 1971; i < y; ++i)
		sum += 365 + isLeap(i);
	for (int i = 1; i < m; ++i)
		sum += days[i];
	if (m > 2)
		sum += isLeap(y);
	sum += d;
	return sum;
}

void s2d(string const& s, int& y, int& m, int& d)
{
	y = (s[0] - '0') * 1000 + (s[1] - '0') * 100
		+ (s[2] - '0') * 10 + (s[3] - '0');
	m = (s[5] - '0') * 10 + (s[6] - '0');
	d = (s[8] - '0') * 10 + (s[9] - '0');
}

int daysBetweenDates(string s, string t)
{
	int y, m, d, a, b;
	s2d(s, y, m, d);
	a = from1971(y, m, d);
	s2d(t, y, m, d);
	b = from1971(y, m, d);
	return abs(a - b);
}


int main()
{
	OutExpr(daysBetweenDates("2020-01-15", "2019-12-31"), "%d");
	OutExpr(daysBetweenDates("2074-09-12", "1983-01-08"), "%d");
}
