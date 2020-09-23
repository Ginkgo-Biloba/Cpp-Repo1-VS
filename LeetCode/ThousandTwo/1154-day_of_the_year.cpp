#include "leetcode.hpp"

/* 1154. 一年中的第几天

给你一个按 YYYY-MM-DD 格式表示日期的字符串 date，请你计算并返回该日期是当年的第几天。

通常情况下，我们认为 1 月 1 日是每年的第 1 天，1 月 2 日是每年的第 2 天，依此类推。
每个月的天数与现行公元纪年法（格里高利历）一致。

示例 1：
输入：date = "2019-01-09"
输出：9

示例 2：
输入：date = "2019-02-10"
输出：41

示例 3：
输入：date = "2003-03-01"
输出：60

示例 4：
输入：date = "2004-03-01"
输出：61

提示：
	date.length == 10
	date[4] == date[7] == '-'，其他的 date[i] 都是数字。
	date 表示的范围从 1900 年 1 月 1 日至 2019 年 12 月 31 日。
*/

static int const A[12] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 12
};

class Solution
{
public:
	int dayOfYear(string date)
	{
		int Y, M, D;
		Y = (date[0] - '0') * 1000
			+ (date[1] - '0') * 100
			+ (date[2] - '0') * 10
			+ (date[3] - '0');
		M = (date[5] - '0') * 10
			+ (date[6] - '0');
		D = (date[8] - '0') * 10
			+ (date[9] - '0');

		for (int i = 0; i < M - 1; ++i)
			D += A[i];
		if ((2 < M)
			&& ((Y % 400 == 0) || ((Y % 4 == 0) && (Y % 100 != 0))))
			++D;
		return D;
	}
};

int main()
{
	Solution s;
	OutExpr(s.dayOfYear("2019-01-09"), "%d");
	OutExpr(s.dayOfYear("2019-02-10"), "%d");
	OutExpr(s.dayOfYear("2003-03-01"), "%d");
	OutExpr(s.dayOfYear("2004-03-01"), "%d");
	OutExpr(s.dayOfYear("1900-03-01"), "%d");
}
