#include "leetcode.hpp"

/* 552. 学生出勤记录 II

给定一个正整数 n，返回长度为 n 的所有可被视为可奖励的出勤记录的数量。
答案可能非常大，你只需返回结果mod 10^9 + 7的值。

学生出勤记录是只包含以下三个字符的字符串：
		'A' : Absent，缺勤
		'L' : Late，迟到
		'P' : Present，到场
如果记录不包含多于一个'A'（缺勤）或超过两个连续的'L'（迟到），则该记录被视为可奖励的。

示例 1:
输入: n = 2
输出: 8
解释：
有8个长度为2的记录将被视为可奖励：
"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
只有"AA"不会被视为可奖励，因为缺勤次数超过一次。

注意：n 的值不会超过100000。
*/

// https://leetcode.com/problems/student-attendance-record-ii/discuss/101643/Share-my-O(n)-C%2B%2B-DP-solution-with-thinking-process-and-explanation
// 抄的
int checkRecord(int n)
{
	int const m = 1e9 + 7;
	if (n == 1)
		return 3;
	vector<int> P(n + 1), L(n + 2), A(n + 3);
	P[0] = 1;
	L[0] = 1;
	L[1] = 3;
	A[0] = 1;
	A[1] = 2;
	A[2] = 4;
	for (int i = 1; i < n; ++i)
	{
		P[i] = ((A[i - 1] + P[i - 1]) % m + L[i - 1]) % m;
		if (i > 1)
			L[i] = ((A[i - 1] + P[i - 1]) % m + (A[i - 2] + P[i - 2]) % m) % m;
		if (i > 2)
			A[i] = ((A[i - 1] + A[i - 2]) % m + A[i - 3]) % m;
	}
	return ((A[n - 1] + P[n - 1]) % m + L[n - 1]) % m;
}


int main()
{
	vector<int> box = { 1, 3, 2, 2, 2, 3, 4, 3, 1 };
	OutExpr(checkRecord(2), "%d");
}
