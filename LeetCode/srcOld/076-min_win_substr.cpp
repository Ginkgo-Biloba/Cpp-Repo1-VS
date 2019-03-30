#include "../srcOld/utility.hpp"

/* Given a string S and a string T,
 * find the minimum window in S which will contain all the characters in T in complexity O(n) */

// https://leetcode.com/problems/minimum-window-substring/discuss/26917/16ms-simple-and-neat-c%2B%2B-solution-only-using-a-vector.-Detailed-explanation
// 抄的
string minWindow(string const& src, string const& target)
{
	int const slen = static_cast<int>(src.size());
	int remain[128] = { 0 };
	int require = static_cast<int>(target.size());
	int minlen = INT_MAX, start = 0, left = 0, i = 0;
	string ans;

	for (int t = 0; t < require; ++t)
		++(remain[target[t]]);

	while (i <= slen && start < slen)
	{
		if (require)
		{
			if (i == slen) break;
			--(remain[src[i]]);
			if (remain[src[i]] >= 0) --require;
			++i;
		}
		else
		{
			if (i - start < minlen)
			{
				minlen = i - start;
				left = start;
			}
			++(remain[src[start]]);
			if (remain[src[start]] > 0) ++require;
			++start;
		}
	}

	if (minlen != INT_MAX)
		ans = src.substr(left, minlen);
	return ans;
}


int main()
{
	string src = "ADOBECODEBANC", target = "ABC";
	printf("%s\n", minWindow(src, target).c_str());
}
