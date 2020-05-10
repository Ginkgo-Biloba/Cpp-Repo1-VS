#include "leetcode.hpp"

/* 18. 四数之和

给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

注意：
答案中不可以包含重复的四元组。

示例：
给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。
满足要求的四元组集合为：
[
	[-1,  0, 0, 1],
	[-2, -1, 1, 2],
	[-2,  0, 0, 2]
]
*/

class Solution
{
	char buffer[64];

	string sign(vector<int>& v)
	{
		sprintf(buffer, "%d %d %d %d", v[0], v[1], v[2], v[3]);
		return string(buffer);
	}

public:
	vector<vector<int>> fourSum(vector<int>& A, int target)
	{
		unordered_set<string> hash;
		vector<vector<int>> res;
		vector<int> quad(4);
		int len = static_cast<int>(A.size());
		int i1, i2, i3, i4, sum;
		string s;

		sort(A.begin(), A.end());
		for (i1 = 0; i1 < len; ++i1)
		{
			quad[0] = A[i1];
			for (i2 = i1 + 1; i2 < len; ++i2)
			{
				quad[1] = A[i2];
				i3 = i2 + 1;
				i4 = len - 1;
				while (i3 < i4)
				{
					sum = A[i1] + A[i2] + A[i3] + A[i4];
					if (sum < target)
						++i3;
					else if (sum > target)
						--i4;
					else
					{
						quad[2] = A[i3];
						quad[3] = A[i4];
						s = sign(quad);
						if (hash.find(s) == hash.end())
						{
							res.push_back(quad);
							hash.insert(s);
						}
						do
						{
							++i3;
						} while (i3 < i4 && A[i3 - 1] == A[i3]);
					}
				}
			}
		}
		hash.clear();
		return res;
	}
};


int main()
{
	vector<int> a = { 1, 0, -1, 0, -2, 2 };
	Solution s;
	output(s.fourSum(a, 0));
}
