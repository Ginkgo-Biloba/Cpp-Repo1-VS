#include "leetcode.hpp"

/* 646. 最长数对链

给出 n 个数对。 在每一个数对中，第一个数字总是比第二个数字小。
现在，我们定义一种跟随关系，当且仅当 b < c 时，数对(c, d) 才可以跟在 (a, b) 后面。
我们用这种形式来构造一个数对链。
给定一个对数集合，找出能够形成的最长数对链的长度。
你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。

示例 :
输入: [[1,2], [2,3], [3,4]]
输出: 2
解释: 最长的数对链是 [1,2] -> [3,4]

注意：
	给出数对的个数在 [1, 1000] 范围内。
*/

// https://leetcode.com/problems/maximum-length-of-pair-chain/discuss/105617/C%2B%2B-Clean-Code
// 抄的
typedef vector<int> range;
int findLongestChain(vector<range>& pairs)
{
	sort(pairs.begin(), pairs.end(),
		[](range const& x, range const& y) -> bool
	{
		return (x[1] < y[1]);
	});

	int count = 1, right = pairs[0][1];
	int len = static_cast<int>(pairs.size());
	for (int i = 1; i < len; ++i)
		if (pairs[i][0] > right)
		{
			right = pairs[i][1];
			++count;
		}
	return count;
}


int main()
{
	vector<range> pairs = { { 1, 2 }, { 2, 3 }, { 3, 4 } };
	OutExpr(findLongestChain(pairs), "%d");
}
