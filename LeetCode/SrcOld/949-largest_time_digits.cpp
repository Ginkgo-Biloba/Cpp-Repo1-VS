#include "leetcode.hpp"

/* 949. 给定数字能组成的最大时间

给定一个由 4 位数字组成的数组，返回可以设置的符合 24 小时制的最大时间。

最小的 24 小时制时间是 00:00，而最大的是 23:59。从 00:00（午夜）开始算起，过得越久，时间越大。

以长度为 5 的字符串返回答案。如果不能确定有效时间，则返回空字符串。

示例 1：
输入：[1,2,3,4]
输出："23:41"

示例 2：
输入：[5,5,5,5]
输出：""

提示：
	A.length == 4
	0 <= A[i] <= 9
*/

string largestTimeFromDigits(vector<int>& A)
{
	char buf[8];
	sort(A.begin(), A.end(), std::greater<int>());
	do
	{
		int h = A[0] * 10 + A[1];
		int m = A[2] * 10 + A[3];
		if (h < 24 && m < 60)
		{
			sprintf(buf, "%02d:%02d", h, m);
			return string(buf);
		}
	} while (prev_permutation(A.begin(), A.end()));
	return string();
}

int main()
{
	vector<int>
		a = { 1, 2, 3, 4 },
		b = { 5, 5, 5, 5 };
	OutString(largestTimeFromDigits(a));
	OutString(largestTimeFromDigits(b));
}
