#include "leetcode.hpp"

/* 935. 骑士拨号器

国际象棋中的骑士可以按下图所示进行移动：（马走日）
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/11/03/keypad.png

这一次，我们将 “骑士” 放在电话拨号盘的任意数字键（如上图所示）上，接下来，骑士将会跳 N-1 步。
每一步必须是从一个数字键跳到另一个数字键。

每当它落在一个键上（包括骑士的初始位置），都会拨出键所对应的数字，总共按下 N 位数字。

你能用这种方式拨出多少个不同的号码？

因为答案可能很大，所以输出答案模 10^9 + 7。

示例 1：
输入：1
输出：10

示例 2：
输入：2
输出：20

示例 3：
输入：3
输出：46

提示：
	1 <= N <= 5000
*/


int knightDialer(int N)
{
	unsigned const Mod = 1e9 + 7;
	unsigned buf[20], *A = buf, *B = buf + 10;
	for (int i = 0; i < 10; ++i)
		A[i] = 1;
	for (--N; N > 0; --N)
	{
		B[0] = (A[4] + A[6]) % Mod;
		B[1] = (A[6] + A[8]) % Mod;
		B[2] = (A[7] + A[9]) % Mod;
		B[3] = (A[4] + A[8]) % Mod;
		B[4] = (A[0] + A[3] + A[9]) % Mod;
		B[5] = 0; // 题目说必须跳不一样的键
		B[6] = (A[0] + A[1] + A[7]) % Mod;
		B[7] = (A[2] + A[6]) % Mod;
		B[8] = (A[1] + A[3]) % Mod;
		B[9] = (A[2] + A[4]) % Mod;
		std::swap(A, B);
	}
	for (int i = 1; i < 10; ++i)
		A[0] = (A[0] + A[i]) % Mod;
	return static_cast<int>(A[0]);
}

int main()
{
	OutExpr(knightDialer(1), "%d");
	OutExpr(knightDialer(2), "%d");
	OutExpr(knightDialer(3), "%d");
	OutExpr(knightDialer(4), "%d");
}
