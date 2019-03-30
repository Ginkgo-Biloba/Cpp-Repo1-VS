#include "../srcOld/utility.hpp"


vector<int> productExceptSelf(vector<int>& nums)
{
	size_t const len = nums.size();
	vector<int> prod(len, 1);
	int left = 1, right = 1;

	for (size_t i = 0; i < len; ++i)
	{
		prod[i] *= left;
		prod[len - 1 - i] *= right;
		left *= nums[i]; right *= nums[len - i - 1];
	}

	return prod;
}


int main()
{
	vector<int> nums = { 1, 2, 3, 4 };
	vector<int> prod = productExceptSelf(nums);
	output(prod, "productExceptSelf");
}

