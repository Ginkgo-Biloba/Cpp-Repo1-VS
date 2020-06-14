#include "leetcode.hpp"

/* 1432. 改变一个整数能得到的最大差值

给你一个整数 num 。你可以对它进行如下步骤恰好 两次 ：

	选择一个数字 x (0 <= x <= 9).
	选择另一个数字 y (0 <= y <= 9) 。数字 y 可以等于 x 。
	将 num 中所有出现 x 的数位都用 y 替换。
	得到的新的整数 不能 有前导 0 ，得到的新整数也 不能 是 0 。

令两次对 num 的操作得到的结果分别为 a 和 b 。

请你返回 a 和 b 的 最大差值 。

示例 1：
输入：num = 555
输出：888
解释：第一次选择 x = 5 且 y = 9 ，并把得到的新数字保存在 a 中。
第二次选择 x = 5 且 y = 1 ，并把得到的新数字保存在 b 中。
现在，我们有 a = 999 和 b = 111 ，最大差值为 888

示例 2：
输入：num = 9
输出：8
解释：第一次选择 x = 9 且 y = 9 ，并把得到的新数字保存在 a 中。
第二次选择 x = 9 且 y = 1 ，并把得到的新数字保存在 b 中。
现在，我们有 a = 9 和 b = 1 ，最大差值为 8

示例 3：
输入：num = 123456
输出：820000

示例 4：
输入：num = 10000
输出：80000

示例 5：
输入：num = 9288
输出：8700

提示：
	1 <= num <= 10^8
*/

int replace(vector<int>& A, int s, int d)
{
	int i = static_cast<int>(A.size());
	int n = 0;
	for (--i; i >= 0; --i)
	{
		n *= 10;
		if (A[i] == s)
			n += d;
		else
			n += A[i];
	}
	return n;
}

int maxDiff0(int num)
{
	int p = num, q = num, k = num;
	vector<int> A;
	for (; k > 0; k /= 10)
		A.push_back(k % 10);

	int len = static_cast<int>(A.size());
	if (len == 1)
		return 8;

	k = len - 1;
	for (; k >= 0; --k)
	{
		if (A[k] != 9)
			break;
	}
	if (k >= 0)
		p = replace(A, A[k], 9);

	k = len - 1;
	if (A[k] != 1)
		q = replace(A, A[k], 1);
	else
	{
		for (; k >= 0; --k)
		{
			if (A[k] > 1)
				break;
		}
		if (k >= 0)
			q = replace(A, A[k], 0);
	}

	return p - q;
}


void replace(char const* src, char* dst, char s, char d)
{
	for (; *src; ++src, ++dst)
	{
		if (*src == s)
			*dst = d;
		else
			*dst = *src;
	}
}


int maxDiff(int num)
{
	int p = num, q = num, k;
	char src[16] = { 0 }, dst[16] = { 0 };
	sprintf(src, "%d", num);
	for (char s = '0'; s <= '9'; ++s)
		for (char d = '0'; d <= '9'; ++d)
		{
			replace(src, dst, s, d);
			k = atoi(dst);
			if ((dst[0] == '0') || (k == 0))
				continue;
			p = max(p, k);
			q = min(q, k);
		}
	return p - q;
}


int main()
{
	OutExpr(maxDiff(555), "%d");
	OutExpr(maxDiff(9), "%d");
	OutExpr(maxDiff(123456), "%d");
	OutExpr(maxDiff(10000), "%d");
	OutExpr(maxDiff(9288), "%d");
}
