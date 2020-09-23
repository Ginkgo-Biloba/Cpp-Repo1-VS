#include "leetcode.hpp"

/* 1017. 负二进制转换

给出数字 N，返回由若干 "0" 和 "1"组成的字符串，该字符串为 N 的负二进制（base -2）表示。

除非字符串就是 "0"，否则返回的字符串中不能含有前导零。

示例 1：
输入：2
输出："110"
解释：(-2) ^ 2 + (-2) ^ 1 = 2

示例 2：
输入：3
输出："111"
解释：(-2) ^ 2 + (-2) ^ 1 + (-2) ^ 0 = 3

示例 3：
输入：4
输出："100"
解释：(-2) ^ 2 = 4

提示：
	0 <= N <= 10^9
*/


// https://en.wikipedia.org/wiki/Negative_base
// https://leetcode.com/problems/convert-to-base-2/discuss/265507/JavaC%2B%2BPython-2-lines-Exactly-Same-as-Base-2
// 抄的
string baseNeg2(int n)
{
	string s;
	while (n)
	{
		s.push_back(static_cast<char>((n & 1) + '0'));
		n = -(n >> 1);
	}
	reverse(s.begin(), s.end());
	if (s.empty())
		s.push_back(0);
	return s;
}


int main()
{
	OutString(baseNeg2(-4));
	OutString(baseNeg2(2));
	OutString(baseNeg2(3));
	OutString(baseNeg2(4));
}
