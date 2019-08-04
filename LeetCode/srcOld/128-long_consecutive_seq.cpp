#include "leetcode.hpp"

/* Given an unsorted array of integers,
 * find the length of the longest consecutive elements sequence.
 * Your algorithm should run in O(n) complexity. */

// https://leetcode.com/problems/longest-consecutive-sequence/discuss/41060/A-simple-C%2B%2Bsolution-using-unordered_set.And-simple-consideration-about-this-problem
// 最长递增序列
// 抄的
int longestConsecutive(vector<int> const& nums)
{
	unordered_set<int> record(nums.begin(), nums.end());
	int ans = 0;
	for (int n : nums)
	{
		if (record.find(n) == record.end()) continue;
		record.erase(n);
		int prev = n - 1, next = n + 1;
		// 找到后，移除连续的元素，是理论上 O(N) 的关键
		while (record.find(prev) != record.end()) record.erase(prev--);
		while (record.find(next) != record.end()) record.erase(next++);
		ans = std::max(ans, next - prev - 1);
	}
	return ans;
};


int main()
{
	vector<int> nums = { 100, 4, 200, 1, 3, 2 };
	printf("longestConsecutive: %d\n", longestConsecutive(nums));
}
