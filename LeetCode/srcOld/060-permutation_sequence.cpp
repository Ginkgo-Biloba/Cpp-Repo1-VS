#include "../srcOld/utility.hpp"

// https://leetcode.com/problems/permutation-sequence/discuss/22507/%22Explain-like-I'm-five%22-Java-Solution-in-O(n)
// 抄的
string getPermutation(int n, int k)
{
	string ans; ans.reserve(n);
	vector<int> fact, nums; 
	fact.resize(n); nums.resize(n);
	fact[0] = 1; nums[0] = 1;
	for (int i = 1; i < n; ++i)
	{
		fact[i] = fact[i - 1] * i;
		nums[i] = i + 1;
	}

	--k;
	for (int i = 1; i <= n; ++i)
	{
		int idx = k / fact[n - i];
		ans.push_back(static_cast<char>('0' + nums[idx]));
		nums.erase(nums.begin() + idx);
		k -= idx * fact[n - i];
	}

	return ans;
}

int main()
{
	int n = 4, k = 9;
	printf("%s\n", getPermutation(n,k).c_str());
}
