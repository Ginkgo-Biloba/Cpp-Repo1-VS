#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
typedef vector<int> vint;

int threeSumCloest(vint& nums, int sum)
{
	int ans = INT_MAX, cur, val;
	size_t i, j, k, sz = nums.size();
	if (sz < 3) return ans;
	sort(nums.begin(), nums.end());
	for (i = 0u; i < sz - 2u; i++)
	{
		cur = sum - nums[i];
		j = i + 1u; k = sz - 1u;
		// 2 sum
		while (j < k)
		{
			val = cur - nums[j] - nums[k];
			if (val == 0) { i = sz; ans = 0; break; }
			else if (abs(val) < abs(ans)) ans = val;
			if (val < 0) k--;
			else j++;
		}
		// unique
		while (i + 1 < sz/*-2*/ && nums[i] == nums[i + 1u])
			i++;
	}
	return (sum - ans);
}

int main()
{
	vint nums{ -1, 2, 1, -4 };
	int sum = 1;
	int ans = threeSumCloest(nums, sum);
	cout << setiosflags(ios::showpos) << ans << "\n";
	return 0;
}