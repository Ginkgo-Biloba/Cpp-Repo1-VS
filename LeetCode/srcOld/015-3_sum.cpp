#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
typedef vector<int> vint;

vector<vint> threeSum(vint& nums)
{
	vector<vint> ans;
	size_t i, j, k, sz = nums.size();
	if (sz < 3) return ans;
	sort(nums.begin(), nums.end());
	vint t(3); int val;
	for (i = 0u; i < sz && nums[i] <= 0; i++)
	{
		t[0] = nums[i];
		j = i + 1u; k = sz - 1u;
		// 2 sum
		while (j < k)
		{
			val = nums[j] + nums[k];
			if (val == -t[0])
			{
				t[1] = nums[j]; t[2] = nums[k];
				ans.push_back(t);
				// unique
				while (j + 1u < k && nums[j] == nums[j + 1u])
					j++;
				j++;
			}
			else if (val > -t[0]) k--;
			else if (val < -t[0]) j++;
		}
		// unique
		while (i + 1 < sz/*-2*/ && nums[i] == nums[i + 1u])
			i++;
	}
	return ans;
}

int main()
{
	vint nums{ -1, 0, 1, 2, -1, -4 };
	vector<vint> ans = threeSum(nums);
	for (vint const& vi : ans)
	{
		for (int const& i : vi)
			cout << setiosflags(ios::showpos) << i << "  ";
		cout << "\n";
	}
	return 0;
}