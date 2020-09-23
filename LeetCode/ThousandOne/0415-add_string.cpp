#include "leetcode.hpp"

/* 415. 字符串相加

给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和。

注意：

num1 和num2 的长度都小于 5100.
num1 和num2 都只包含数字 0-9.
num1 和num2 都不包含任何前导零。
你不能使用任何內建 BigInteger 库， 也不能直接将输入的字符串转换为整数形式。
*/


string addStrings(string const& A, string const& B)
{
	// A 比 B 长
	if (A.size() < B.size())
		return addStrings(B, A);
	if (B.empty())
		return A;

	size_t iA = A.size(), iB = B.size();
	size_t sz1 = static_cast<size_t>(-1);
	string C; C.reserve(iA + 1);
	int carry = 0;
	for (--iA, --iB; iB != sz1; --iA, --iB)
	{
		int sum = B[iB] + A[iA] + carry - 2 * '0';
		carry = (sum >= 10);
		sum -= carry * 10;
		C.push_back(static_cast<char>(sum + '0'));
	}
	for (; iA != sz1; --iA)
	{
		int sum = A[iA] + carry - '0';
		carry = (sum >= 10);
		sum -= carry * 10;
		C.push_back(static_cast<char>(sum + '0'));
	}
	if (carry > 0)
		C.push_back(static_cast<char>(carry + '0'));

	std::reverse(C.begin(), C.end());
	return C;
}


int main()
{
	OutExpr(addStrings("5", "408").c_str(), "%s");
}
