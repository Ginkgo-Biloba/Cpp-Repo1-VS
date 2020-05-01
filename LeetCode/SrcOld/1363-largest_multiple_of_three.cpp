#include "leetcode.hpp"

/* 1363. 形成三的最大倍数

给你一个整数数组 digits，你可以通过按任意顺序连接其中某些数字来形成 3 的倍数，请你返回所能得到的最大的 3 的倍数。

由于答案可能不在整数数据类型范围内，请以字符串形式返回答案。

如果无法得到答案，请返回一个空字符串。

示例 1：
输入：digits = [8,1,9]
输出："981"

示例 2：
输入：digits = [8,6,7,1,0]
输出："8760"

示例 3：
输入：digits = [1]
输出：""

示例 4：
输入：digits = [0,0,0,0,0,0]
输出："0"

提示：
	1 <= digits.length <= 10^4
	0 <= digits[i] <= 9
	返回的结果不应包含不必要的前导零。
*/

// https://leetcode.com/problems/largest-multiple-of-three/discuss/518830/C%2B%2BJava-Concise-O(n)
// 抄的
string largestMultipleOfThree(vector<int>& digits)
{
	int m1[] = { 1, 4, 7, 2, 5, 8 };
	int m2[] = { 2, 5, 8, 1, 4, 7 };
	int sum = 0, cnt[10] = { 0 };
	for (int d : digits)
	{
		sum += d;
		++(cnt[d]);
	}
	while (sum % 3 != 0)
	{
		int* ptr = (sum % 3 == 1) ? m1 : m2;
		for (int d = 0; d < 6; ++d)
		{
			int i = ptr[d];
			if (cnt[i])
			{
				--(cnt[i]);
				sum -= i;
				break;
			}
		}
	}
	string s;
	for (int d = 9; d >= 0; --d)
		for (int i = cnt[d]; i > 0; --i)
			s.push_back(static_cast<char>(d + '0'));
	if (!s.empty() && s[0] == '0')
		string("0").swap(s);
	return s;
}


int main()
{
	vector<int>
		a = { 8, 1, 9 },
		b = { 8, 6, 7, 1, 0 },
		c = { 1 },
		d = { 0, 0, 0, 0 };
	OutString(largestMultipleOfThree(a));
	OutString(largestMultipleOfThree(b));
	OutString(largestMultipleOfThree(c));
	OutString(largestMultipleOfThree(d));
}
