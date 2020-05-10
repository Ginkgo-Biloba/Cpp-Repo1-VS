#include "leetcode.hpp"

/* 43. 字符串相乘

给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

示例 1:
输入: num1 = "2", num2 = "3"
输出: "6"

示例 2:
输入: num1 = "123", num2 = "456"
输出: "56088"

说明：
	num1 和 num2 的长度小于110。
	num1 和 num2 只包含数字 0-9。
	num1 和 num2 均不以零开头，除非是数字 0 本身。
	不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。
*/

string multiply(string A, string B)
{
	if (A.length() < B.length())
		A.swap(B);
	int a = static_cast<int>(A.length());
	int b = static_cast<int>(B.length());
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());
	// 最多 a + b 位
	string C(a + b, 0);
	for (int k = 0; k < a; ++k)
		A[k] = static_cast<char>(A[k] - '0');
	for (int i = 0; i < b; ++i)
		B[i] = static_cast<char>(B[i] - '0');
	for (int i = 0; i < b; ++i)
	{
		if (B[i] == 0)
			continue;
		div_t bit = { 0, 0 };
		for (int k = 0; k < a; ++k)
		{
			bit.quot += C[i + k] + B[i] * A[k];
			bit = div(bit.quot, 10);
			C[i + k] = static_cast<char>(bit.rem);
		}
		for (int k = i + a; bit.quot > 0; ++k)
		{
			bit.quot += C[k];
			bit = div(bit.quot, 10);
			C[k] = static_cast<char>(bit.rem);
		}
	}
	while ((C.size() > 1) && (C.back() == 0))
		C.pop_back();
	int c = static_cast<int>(C.length());
	for (int i = 0; i < c; ++i)
		C[i] = static_cast<char>(C[i] + '0');
	reverse(C.begin(), C.end());
	return C;
}

int main()
{
	OutString(multiply("2", "3"));
	OutString(multiply("123", "456"));
	OutString(multiply("2", "97"));
}
