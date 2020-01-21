#include "leetcode.hpp"

/* 1051. 高度检查器

学校在拍年度纪念照时，一般要求学生按照非递减的高度顺序排列。
请你返回至少有多少个学生没有站在正确位置数量。
该人数指的是：能让所有学生以 非递减 高度排列的必要移动人数。

示例：
输入：[1,1,4,2,1,3]
输出：3
解释：
高度为 4、3 和最后一个 1 的学生，没有站在正确的位置。

提示：
	1 <= heights.length <= 100
	1 <= heights[i] <= 100
*/

int heightChecker(vector<int>& A)
{
	vector<int> B = A;
	size_t len = A.size();
	int ans = 0;
	sort(A.begin(), A.end());
	for (size_t i = 0; i < len; ++i)
		ans += (A[i] != B[i]);
	return ans;
}


int main()
{
	vector<int> a = { 1, 1, 4, 2, 1, 3 };
	OutExpr(heightChecker(a), "%d");
}
