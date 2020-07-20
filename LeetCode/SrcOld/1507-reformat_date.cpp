#include "leetcode.hpp"

/* 1507. 转变日期格式

给你一个字符串 date ，它的格式为 Day Month Year ，其中：
	Day 是集合 {"1st", "2nd", "3rd", "4th", ..., "30th", "31st"} 中的一个元素。
	Month 是集合 {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"} 中的一个元素。
	Year 的范围在 ​[1900, 2100] 之间。

请你将字符串转变为 YYYY-MM-DD 的格式，其中：
	YYYY 表示 4 位的年份。
	MM 表示 2 位的月份。
	DD 表示 2 位的天数。

示例 1：
输入：date = "20th Oct 2052"
输出："2052-10-20"

示例 2：
输入：date = "6th Jun 1933"
输出："1933-06-06"

示例 3：
输入：date = "26th May 1960"
输出："1960-05-26"

提示：
	给定日期保证是合法的，所以不需要处理异常输入。
*/

static char const* month[] =
{
	"Jan", "Feb", "Mar", "Apr",
	"May", "Jun", "Jul", "Aug",
	"Sep", "Oct", "Nov", "Dec",
};

string reformatDate(string date)
{
	int Y = 0, M = 0, D = 0;
	size_t i = date.find_first_of(' ') + 1;
	D = atoi(date.data());
	for (int m = 0; m < 12; ++m)
		if (!memcmp(month[m], date.data() + i, 3 * sizeof(char)))
		{
			M = m + 1;
			break;
		}
	i = date.find_first_of(' ', i + 1) + 1;
	Y = atoi(date.data() + i);
	char buf[16];
	snprintf(buf, sizeof(buf),
		"%04d-%02d-%02d", Y, M, D);
	return string(buf);
}

int main()
{
	OutString(reformatDate("20th Oct 2052"));
	OutString(reformatDate("6th Jun 1933"));
	OutString(reformatDate("26th May 1960"));
}
