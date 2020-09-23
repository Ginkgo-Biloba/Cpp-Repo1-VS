#include "leetcode.hpp"

/* 551. 学生出勤记录 I

给定一个字符串来代表一个学生的出勤记录，这个记录仅包含以下三个字符：
		'A' : Absent，缺勤
		'L' : Late，迟到
		'P' : Present，到场
如果一个学生的出勤记录中不超过一个'A'(缺勤)并且不超过两个连续的'L'(迟到),那么这个学生会被奖赏。

你需要根据这个学生的出勤记录判断他是否会被奖赏。

示例 1:
输入: "PPALLP"
输出: True

示例 2:
输入: "PPALLL"
输出: False
*/


bool checkRecord(string s)
{
	size_t len = s.size();
	if (len == 0)
		return true;
	int L = 0, A = 0;
	for (size_t i = 0; i < len; ++i)
	{
		if (s[i] == 'L')
		{
			++L;
			if (L > 2)
				return false;
		}
		else
		{
			L = 0;
			if (s[i] == 'A')
			{
				++A;
				if (A > 1)
					return false;
			}
		}
	}
	return true;
}


int main()
{
	OutExpr(boolstr[checkRecord("PPALLL")], "%s");
}
