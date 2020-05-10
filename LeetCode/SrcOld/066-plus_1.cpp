#include "leetcode.hpp"

/* 66. 加一

给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

示例 1:
输入: [1,2,3]
输出: [1,2,4]
解释: 输入数组表示数字 123。

示例 2:
输入: [4,3,2,1]
输出: [4,3,2,2]
解释: 输入数组表示数字 4321。
*/

vector<int> plusOne(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	div_t q = { 0, 0 };
	q.quot = 1;
	reverse(A.begin(), A.end());
	for (int i = 0; i < len; ++i)
	{
		q.quot += A[i];
		q = div(q.quot, 10);
		A[i] = q.rem;
		if (q.quot == 0)
			break;
	}
	if (q.quot)
		A.push_back(1);
	reverse(A.begin(), A.end());
	vector<int> B;
	B.swap(A);
	return B;
}

int main()
{
	vector<int>
		a = { 1, 2, 3 },
		b = { 4, 3, 2, 1 },
		c = { 9, 9, 9 };
	output(plusOne(a));
	output(plusOne(b));
	output(plusOne(c));
}
