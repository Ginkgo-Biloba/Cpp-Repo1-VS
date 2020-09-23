#include "leetcode.hpp"

/* 169. 多数元素

给定一个大小为 n 的数组，找到其中的多数元素。
多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

示例 1:
输入: [3,2,3]
输出: 3

示例 2:
输入: [2,2,1,1,1,2,2]
输出: 2
*/

int majorityElement(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int ans = A[0], cnt = 1;
	for (int i = 1; i < len; ++i)
	{
		if (cnt == 0)
			ans = A[i];
		if (ans == A[i])
			++cnt;
		else
			--cnt;
	}
	return ans;
}


int main()
{
	vector<int>
		a = { 3, 2, 3 },
		b = { 2, 2, 1, 1, 1, 2, 2 };
	OutExpr(majorityElement(a), "%d");
	OutExpr(majorityElement(b), "%d");
}
