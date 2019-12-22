#include "leetcode.hpp"

/* 896. 单调数列

如果数组是单调递增或单调递减的，那么它是单调的。

如果对于所有 i <= j，A[i] <= A[j]，那么数组 A 是单调递增的。
如果对于所有 i <= j，A[i]> = A[j]，那么数组 A 是单调递减的。

当给定的数组 A 是单调数组时返回 true，否则返回 false。

示例 1：
输入：[1,2,2,3]
输出：true

示例 2：
输入：[6,5,4,4]
输出：true

示例 3：
输入：[1,3,2]
输出：false

示例 4：
输入：[1,2,4,5]
输出：true

示例 5：
输入：[1,1,1]
输出：true

提示：
	1 <= A.length <= 50000
	-100000 <= A[i] <= 100000
*/

bool isMonotonic1(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int dir = 0;

	for (int i = 1; i < len; ++i)
	{
		int d = A[i] - A[i - 1];
		if (dir == 0)
			dir = d;
		else if (false
			|| (d < 0 && dir > 0)
			|| (d > 0 && dir < 0))
			return false;
	}

	return true;
}

// https://leetcode.com/problems/monotonic-array/discuss/165889/C%2B%2BJavaPython-One-Pass-O(N)
// 抄的
bool isMonotonic(vector<int>& A)
{
	bool inc = true, dec = true;
	int len = static_cast<int>(A.size());
	for (int i = 1; i < len; ++i)
	{
		inc &= A[i - 1] <= A[i];
		dec &= A[i - 1] >= A[i];
	}
	return inc || dec;
}

int main()
{
	vector<int>
		a = { 1, 2, 2, 3 },
		b = { 6, 5, 4, 4 },
		c = { 1, 3, 2 },
		d = { 1, 2, 4, 5 },
		e = { 1, 1, 1 },
		f = { 1, 1, 0 },
		g = { 11, 11, 9, 4, 3, 3, 3, 1, -1, -1, 3, 3, 3, 5, 5, 5 };
	OutBool(isMonotonic(a));
	OutBool(isMonotonic(b));
	OutBool(isMonotonic(c));
	OutBool(isMonotonic(d));
	OutBool(isMonotonic(e));
	OutBool(isMonotonic(f));
	OutBool(isMonotonic(g));
}
