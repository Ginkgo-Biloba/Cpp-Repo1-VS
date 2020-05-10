#include "leetcode.hpp"

/* 6. Z 字形变换

将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：

L   C   I   R
E T O E S I I G
E   D   H   N

之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);

示例 1:
输入: s = "LEETCODEISHIRING", numRows = 3
输出: "LCIRETOESIIGEDHN"

示例 2:
输入: s = "LEETCODEISHIRING", numRows = 4
输出: "LDREOEIIECIHNTSG"
解释:
L     D     R
E   O E   I I
E C   I H   N
T     S     G
*/

string convert(string s, int numRows)
{
	int len = static_cast<int>(s.length());
	int h = 0, dir = 1;
	vector<string> R(numRows);
	if (numRows == 1)
		return s;
	for (int i = 0; i < len; ++i)
	{
		R[h].push_back(s[i]);
		h += dir;
		if (h == numRows)
		{
			dir = -dir;
			h -= 2;
		}
		if (h == -1)
		{
			dir = -dir;
			h += 2;
		}
	}
	s.clear();
	for (h = 0; h < numRows; ++h)
		s += R[h];
	return s;
}

int main()
{
	OutString(convert("LEETCODEISHIRING", 3));
	OutString(convert("LEETCODEISHIRING", 4));
}
