#include "leetcode.hpp"

/* 1702. 修改后的最大二进制字符串

给你一个二进制字符串 binary ，它仅有 0 或者 1 组成。
你可以使用下面的操作任意次对它进行修改：
	操作 1 ：如果二进制串包含子字符串 "00" ，你可以用 "10" 将其替换。
			比方说， "00010" -> "10010"
	操作 2 ：如果二进制串包含子字符串 "10" ，你可以用 "01" 将其替换。
			比方说， "00010" -> "00001"

请你返回执行上述操作任意次以后能得到的 最大二进制字符串 。
如果二进制字符串 x 对应的十进制数字大于二进制字符串 y 对应的十进制数字，那么我们称二进制字符串 x 大于二进制字符串 y 。

示例 1：
输入：binary = "000110"
输出："111011"
解释：一个可行的转换为：
"000110" -> "000101"
"000101" -> "100101"
"100101" -> "110101"
"110101" -> "110011"
"110011" -> "111011"

示例 2：
输入：binary = "01"
输出："01"
解释："01" 没办法进行任何转换。

提示：
	1 <= binary.length <= 105
	binary 仅包含 '0' 和 '1' 。
*/

string maximumBinaryString1(string s)
{
	int len = static_cast<int>(s.size());
	int C[2] = { 0, 0 };
	int i = 0;
	for (; i < len; ++i)
	{
		if (s[i] == '0')
			break;
	}
	sort(s.begin() + i, s.end());
	for (; i < len - 1; ++i)
	{
		if (s[i + 1] == '0')
			s[i] = '1';
	}
	return s;
}

// https://leetcode.com/problems/maximum-binary-string-after-change/discuss/987335/JavaC%2B%2BPython-Solution-with-Explanation
// 抄的
string maximumBinaryString(string s)
{
	int len = static_cast<int>(s.size());
	int one = 0, zero = 0;
	for (int i = 0; i < len; ++i)
	{
		if (s[i] == '0')
			zero++;
		else if (zero == 0)
			one++;
		s[i] = '1';
	}
	if (one < len)
		s[one + zero - 1] = '0';
	return s;
}


int main()
{}
