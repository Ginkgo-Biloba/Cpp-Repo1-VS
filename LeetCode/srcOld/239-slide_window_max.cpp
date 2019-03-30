#include "../srcOld/utility.hpp"

// 这里用图像腐蚀膨胀（最大值最小值滤波）的方法，没有用评论里面的队列方法
vector<int> maxSlidingWindow(vector<int> const& nums, int k)
{
	if (nums.empty() || k == 1)
		return nums;

	int len = static_cast<int>(nums.size());
	vector<int> ans(len - k + 1);
	vector<int> fwd(len);
	vector<int> bkd(len);
	int nStripe = len / k;
	int fi = 0, bi;

	while (nStripe--)
	{
		bi = fi + k - 1;
		fwd[fi] = nums[fi];
		bkd[bi] = nums[bi];
		fi++; bi--;
		for (int s = k; --s;)
		{
			fwd[fi] = std::max(fwd[fi - 1], nums[fi]);
			bkd[bi] = std::max(bkd[bi + 1], nums[bi]);
			fi++; bi--;
		}
	}
	if (fi < len)
	{
		bi = len - 1;
		fwd[fi] = nums[fi];
		bkd[bi] = nums[bi];
		fi++; bi--;
		while (fi < len)
		{
			fwd[fi] = std::max(fwd[fi - 1], nums[fi]);
			bkd[bi] = std::max(bkd[bi + 1], nums[bi]);
			fi++; bi--;
		}
	}

	bi = len - k + 1;
	for (fi = 0; fi < bi; fi++)
		ans[fi] = std::max(fwd[fi + k - 1], bkd[fi]);

	return ans;
}




int main()
{
	vector<int> nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
	nums = maxSlidingWindow(nums, 3);
	output(nums, "maxSlidingWindow");
}
