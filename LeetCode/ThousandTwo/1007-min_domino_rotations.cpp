#include "leetcode.hpp"

/* 1007. 行相等的最少多米诺旋转

在一排多米诺骨牌中，A[i] 和 B[i] 分别代表第 i 个多米诺骨牌的上半部分和下半部分。（一个多米诺是两个从 1 到 6 的数字同列平铺形成的 —— 该平铺的每一半上都有一个数字。）

我们可以旋转第 i 张多米诺，使得 A[i] 和 B[i] 的值交换。

返回能使 A 中所有值或者 B 中所有值都相同的最小旋转次数。

如果无法做到，返回 -1.



示例 1：
输入：A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
输出：2
解释：
图一表示：在我们旋转之前， A 和 B 给出的多米诺牌。
如果我们旋转第二个和第四个多米诺骨牌，我们可以使上面一行中的每个值都等于 2，如图二所示。
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2019/03/08/domino.png

示例 2：
输入：A = [3,5,1,2,3], B = [3,6,3,3,4]
输出：-1
解释：
在这种情况下，不可能旋转多米诺牌使一行的值相等。

提示：
	1 <= A[i], B[i] <= 6
	2 <= A.length == B.length <= 20000
*/


// https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/discuss/252242/JavaC%2B%2BPython-Different-Ideas
// 抄的
int minDominoRotations(vector<int>& A, vector<int>& B)
{
	int buf[7 * 3] = { 0 };
	int *numA = buf, *numB = buf + 7, *same = buf + 14;
	int len = static_cast<int>(A.size());
	for (int i = 0; i < len; ++i)
	{
		numA[A[i]] += 1;
		numB[B[i]] += 1;
		if (A[i] == B[i])
			same[A[i]] += 1;
	}
	for (int i = 1; i <= 6; ++i)
	{
		int d = numA[i] + numB[i] - same[i];
		if (d == len)
			return len - max(numA[i], numB[i]);
	}
	return -1;
}

int main()
{
	vector<int>
		a = { 2, 1, 2, 4, 2, 2 },
		b = { 5, 2, 6, 2, 3, 2 },
		c = { 3, 5, 1, 2, 3 },
		d = { 3, 6, 3, 3, 4 };
	OutExpr(minDominoRotations(a, b), "%d");
	OutExpr(minDominoRotations(c, d), "%d");
}
