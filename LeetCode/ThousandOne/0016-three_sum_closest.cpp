#include "leetcode.hpp"

/* 16. 最接近的三数之和

给定一个包括 n 个整数的数组 nums 和 一个目标值 target。
找出 nums 中的三个整数，使得它们的和与 target 最接近。
返回这三个数的和。假定每组输入只存在唯一答案。

例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.

与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).
*/

int threeSumClosest(vector<int>& A, int target)
{
	int dif = INT_MAX, cur, val;
	int len = static_cast<int>(A.size());
	if (len < 3)
		return dif;
	sort(A.begin(), A.end());
	for (int i = 0; i < len - 2; i++)
	{
		cur = target - A[i];
		int j = i + 1;
		int k = len - 1;
		// 2 sum
		while (j < k)
		{
			val = cur - A[j] - A[k];
			if (val == 0)
			{
				i = len;
				dif = 0;
				break;
			}
			else if (abs(val) < abs(dif))
				dif = val;
			if (val < 0)
				k--;
			else
				j++;
		}
		// unique
		while (i < len - 1 && A[i] == A[i + 1])
			i++;
	}
	return (target - dif);
}


int main()
{
	vector<int> a = { -1, 2, 1, -4 };
	OutExpr(threeSumClosest(a, 1), "%d");
}
