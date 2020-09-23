#include "leetcode.hpp"

/* 81. 搜索旋转排序数组 II

假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,0,1,2,2,5,6] 可能变为 [2,5,6,0,0,1,2] )。

编写一个函数来判断给定的目标值是否存在于数组中。
若存在返回 true，否则返回 false。

示例 1:
输入: nums = [2,5,6,0,0,1,2], target = 0
输出: true

示例 2:
输入: nums = [2,5,6,0,0,1,2], target = 3
输出: false

进阶:
	这是 搜索旋转排序数组 的延伸题目，本题中的 nums 可能包含重复元素。
	这会影响到程序的时间复杂度吗？会有怎样的影响，为什么？
*/

// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/discuss/28218/My-8ms-C%2B%2B-solution-(o(logn)-on-average-o(n)-worst-case)
// 抄的
int search(vector<int>& A, int val)
{
	int len = static_cast<int>(A.size());
	if (len == 0)
		return false;
	int h = 0, i, k = len - 1;
	while (h < k)
	{
		i = (h + k) / 2;
		if (A[i] == val)
			return true;
		// 退化为 O(N) 如 [3 1 2 3 3 3 3]
		if ((A[h] == A[i]) && (A[i] == A[k]))
		{
			++h;
			--k;
		}
		else if (A[h] <= A[i])
		{
			if (A[h] <= val && val < A[i])
				k = i - 1;
			else
				h = i + 1;
		}
		else
		{
			if (A[i] < val && val <= A[k])
				h = i + 1;
			else
				k = i - 1;
		}
	}
	return A[h] == val;
}


int main()
{
	vector<int> a = { 2, 5, 6, 0, 0, 1, 2 };
	OutExpr(search(a, 0), "%d");
	OutExpr(search(a, 3), "%d");
}
