#include "../srcOld/utility.hpp"

/*
思路：摩尔投票升级版，超过n/3的数最多只能有两个；
先选出两个候选人A,B，遍历数组，如果投A（等于A），则A的票数++; 如果投B，B的票数++；
如果A, B都不投（即与A，B都不相等），那么检查此时是否AB中候选人的票数是否为0，如果为0,则成为新的候选人；
如果A, B两个人的票数都不为0，那么 A,B 两个候选人的票数均--；
遍历结束后选出两个候选人，但是这两个候选人是否满足>n/3，还需要再遍历一遍数组，找出两个候选人的具体票数
*/

// 抄的
vector<int> majorityElement(vector<int>& nums)
{
	vector<int> ans; ans.reserve(2);
	int cand[2], count[2];
	int const len = static_cast<int>(nums.size());
	if (len == 0) return ans;

	// 赋值 cand[1] 只是为了不让路径执行到 else if (n == cand[1]) 里面
	cand[0] = cand[1] = nums[0]; 
	count[0] = 1; count[1] = 0;

	for (int i = 0; i < len; ++i)
	{
		int const n = nums[i];
		if (n == cand[0]) count[0]++;
		else if (n == cand[1]) count[1]++;
		// 此时A,B都不投,检查是否有票数为0情况，如果为0，则更新候选人
		else
		{
			if (count[0] == 0)
			{
				cand[0] = n;
				count[0] = 1;
			}
			if (count[1] == 0)
			{
				cand[1] = n;
				count[1] = 1;
			}
			// 此时两个候选人的票数都大于1，且当前选名不投AB，那么A,B对应的票数都要--
			else
			{
				count[0]--;
				count[1]--;
			}
		}
	}

	// 上一轮遍历找出了两个候选人
	// 但是这两个候选人是否均满足票数大于N/3仍然没法确定，需要重新遍历，确定票数
	count[0] = count[1] = 0;

	for (int i = 0; i < len; ++i)
	{
		int const n = nums[i];
		if (n == cand[0])
			count[0]++;
		else if (n == cand[1])
			count[1]++;
	}

	if (count[0] * 3 > len)
		ans.push_back(cand[0]);
	 if (count[1] * 3 > len)
		ans.push_back(cand[1]);

	return ans;
}


int main()
{
	vector<int> nums = { 1, 1, 1, 3, 3, 2, 2, 2 };
	vector<int> ans = majorityElement(nums);
	output(ans, "majorityElement");
}

