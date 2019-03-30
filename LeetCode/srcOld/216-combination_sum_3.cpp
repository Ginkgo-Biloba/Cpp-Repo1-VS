#include "utility.hpp"

class Solution
{
	int n, k;
	vector<int> vec;

	void backtrack(vector<vector<int>>& ans, int cur, int sum)
	{
		if (n < sum)
			return; // 总和超过给定值
		else if ((n == sum) && (vec.size() == k))
			ans.push_back(vec);

		for (; cur < 10; ++cur)
		{
			vec.push_back(cur);
			backtrack(ans, cur + 1, sum + cur);
			vec.pop_back();
		}
	}

public:
	vector<vector<int>> combinationSum3(int k_, int n_)
	{
		vector<vector<int>> ans;
		n = n_; k = k_;
		vec.clear();
		backtrack(ans, 1, 0);
		return ans;
	}
};



int main()
{
	vector<vector<int>> ans = Solution().combinationSum3(3, 9);
	output(ans, "Combination Sum III");
}
