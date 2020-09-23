#include "leetcode.hpp"

/* 989. 数组形式的整数加法

对于非负整数 X 而言，X 的数组形式是每位数字按从左到右的顺序形成的数组。
例如，如果 X = 1231，那么其数组形式为 [1,2,3,1]。

给定非负整数 X 的数组形式 A，返回整数 X+K 的数组形式。

示例 1：
输入：A = [1,2,0,0], K = 34
输出：[1,2,3,4]
解释：1200 + 34 = 1234

示例 2：
输入：A = [2,7,4], K = 181
输出：[4,5,5]
解释：274 + 181 = 455

示例 3：
输入：A = [2,1,5], K = 806
输出：[1,0,2,1]
解释：215 + 806 = 1021

示例 4：
输入：A = [9,9,9,9,9,9,9,9,9,9], K = 1
输出：[1,0,0,0,0,0,0,0,0,0,0]
解释：9999999999 + 1 = 10000000000

提示：
	1 <= A.length <= 10000
	0 <= A[i] <= 9
	0 <= K <= 10000
	如果 A.length > 1，那么 A[0] != 0
*/

vector<int> addToArrayForm(vector<int>& A, int K)
{
	if (K == 0)
		return A;

	vector<int> B, S;
	B.reserve(32);
	while (K)
	{
		B.push_back(K % 10);
		K /= 10;
	}
	reverse(A.begin(), A.end());
	// 确保 A 长，省得判断
	if (A.size() < B.size())
		A.swap(B);

	int m = static_cast<int>(A.size());
	int n = static_cast<int>(B.size());
	int a = 0, b = 0;
	int digit, carry = 0;
	S.reserve(max(m, n) + 1);
	for (; a < m && b < n; ++a, ++b)
	{
		digit = A[a] + B[b] + carry;
		carry = digit >= 10;
		digit -= carry * 10;
		S.push_back(digit);
	}
	for (; a < m; ++a)
	{
		digit = A[a] + carry;
		carry = digit >= 10;
		digit -= carry * 10;
		S.push_back(digit);
	}
	if (carry)
		S.push_back(carry);

	reverse(S.begin(), S.end());
	return S;
}

int main()
{
	vector<int>
		a = { 1, 2, 0, 0 },
		b = { 2, 7, 4 },
		c = { 2, 1, 5 },
		d = { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 };
	output(addToArrayForm(a, 34), "Add to Array-Form of Integer");
	output(addToArrayForm(b, 181), "Add to Array-Form of Integer");
	output(addToArrayForm(c, 806), "Add to Array-Form of Integer");
	output(addToArrayForm(d, 1), "Add to Array-Form of Integer");
}
