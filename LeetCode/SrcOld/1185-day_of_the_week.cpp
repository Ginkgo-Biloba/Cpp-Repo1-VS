#include "leetcode.hpp"

/* 1185. 一周中的第几天

给你一个日期，请你设计一个算法来判断它是对应一周中的哪一天。

输入为三个整数：day、month 和 year，分别表示日、月、年。

您返回的结果必须是这几个值中的一个 {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}。

示例 1：
输入：day = 31, month = 8, year = 2019
输出："Saturday"

示例 2：
输入：day = 18, month = 7, year = 1999
输出："Sunday"

示例 3：
输入：day = 15, month = 8, year = 1993
输出："Sunday"

提示：
	给出的日期一定是在 1971 到 2100 年之间的有效日期。
*/

// https://leetcode.com/problems/day-of-the-week/discuss/382150/Python3-Solution-With-No-Knowledge-(Without-knowing-formulas-or-week-day-of-111971-beforehand)

static int const day_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool leap_year(int y)
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int day_since_1970(int y, int m, int d)
{
	int s = 0, i = 1970;
	for (; i < y; ++i)
		s += 365 + leap_year(i);
	for (i = 0; i < m - 1; ++i)
		s += day_in_month[i];
	s += d;
	if (m > 2)
		s += leap_year(y);
	return s;
}


string dayOfTheWeek(int day, int month, int year)
{
	// 2020-03-31 Tuesday
	string day_name[] = {
		"Tuesday", "Wednesday", "Thursday", "Friday",
		"Saturday", "Sunday", "Monday"
	};
	int x = day_since_1970(2020, 3, 31);
	int y = day_since_1970(year, month, day);
	int z = (y - x) % 7;
	if (z < 0)
		z += 7;
	return day_name[z];
}


int main()
{
	OutString(dayOfTheWeek(31, 8, 2019));
	OutString(dayOfTheWeek(18, 7, 1999));
	OutString(dayOfTheWeek(15, 8, 1993));
}
