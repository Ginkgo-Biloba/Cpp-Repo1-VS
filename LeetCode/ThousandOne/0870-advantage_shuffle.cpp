#include "leetcode.hpp"

/* 870. 优势洗牌

给定两个大小相等的数组 A 和 B，A 相对于 B 的优势可以用满足 A[i] > B[i] 的索引 i 的数目来描述。

返回 A 的任意排列，使其相对于 B 的优势最大化。

示例 1：
输入：A = [2,7,11,15], B = [1,10,4,11]
输出：[2,11,7,15]

示例 2：
输入：A = [12,24,8,32], B = [13,25,32,11]
输出：[24,32,8,12]

提示：
	1 <= A.length = B.length <= 10000
	0 <= A[i] <= 10^9
	0 <= B[i] <= 10^9
*/

vector<int> advantageCount(vector<int>& A, vector<int>& B)
{
	int len = static_cast<int>(A.size());
	vector<pair<int, int>> C;
	C.reserve(len);

	for (int i = 0; i < len; ++i)
		C.emplace_back(B[i], i);
	sort(C.begin(), C.end());
	sort(A.begin(), A.end());

	int L = 0, R = len - 1;
	for (int i = len - 1; i >= 0; --i)
	{
		if (C[i].first < A[R])
		{
			B[C[i].second] = A[R];
			--R;
		}
		else
		{
			B[C[i].second] = A[L];
			++L;
		}
	}

	return B;
}

int main()
{
	vector<int>
		a0 = { 2, 7, 11, 15 },
		b0 = { 1, 10, 4, 11 },
		a1 = { 12, 24, 8, 32 },
		b1 = { 13, 25, 32, 11 };
	output(advantageCount(a0, b0), "Advantage Shuffle");
	output(advantageCount(a1, b1), "Advantage Shuffle");
}
