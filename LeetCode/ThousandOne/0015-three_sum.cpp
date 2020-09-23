#include "leetcode.hpp"

/* 15. 三数之和

给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？
请你找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例：
给定数组 nums = [-1, 0, 1, 2, -1, -4]，
满足要求的三元组集合为：
[
	[-1, 0, 1],
	[-1, -1, 2]
]
*/

vector<vector<int>> threeSum(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	vector<vector<int>> ans;
	vector<int> R(3);
	if (len < 3) return ans;
	sort(A.begin(), A.end());
	for (int i = 0; i <= len - 3 && A[i] <= 0; ++i)
	{
		R[0] = A[i];
		int j = i + 1;
		int k = len - 1;
		// 2 sum
		while (j < k)
		{
			int val = A[j] + A[k];
			if (val == -R[0])
			{
				R[1] = A[j];
				R[2] = A[k];
				ans.push_back(R);
				// unique
				while (j + 1 < k && A[j] == A[j + 1])
					j++;
				j++;
			}
			else if (val > -R[0])
				k--;
			else if (val < -R[0])
				j++;
		}
		// unique
		while (i <= len - 3 && A[i] == A[i + 1])
			i++;
	}
	return ans;
}


int main()
{
	vector<int>
		a = { -1, 0, 1, 2, -1, -4 },
		b = { -1, 0, 1, 2, -1, 0, 0 };
	output(threeSum(a), "3sum");
	output(threeSum(b), "3sum");
}
