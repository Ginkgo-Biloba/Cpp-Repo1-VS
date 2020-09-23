#include "leetcode.hpp"

/* 1079. 活字印刷

你有一套活字字模 tiles，其中每个字模上都刻有一个字母 tiles[i]。
返回你可以印出的非空字母序列的数目。

示例 1：
输入："AAB"
输出：8
解释：可能的序列为 "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA"。

示例 2：
输入："AAABBC"
输出：188

提示：
		1 <= tiles.length <= 7
		tiles 由大写英文字母组成
*/


// https://leetcode.com/problems/letter-tile-possibilities/discuss/381605/c%2B%2B-0-ms-runtime-(100)
// 抄的 
class Solution
{
	int hist[26];
	int nums;

	void record()
	{
		for (int i = 0; i < 26; ++i)
			if (hist[i])
			{
				--(hist[i]);
				++nums;
				record();
				++(hist[i]);
			}
	}

public:
	int numTilePossibilities(string tiles)
	{
		memset(hist, 0, sizeof(hist));
		nums = 0;
		for (char c : tiles)
			++(hist[static_cast<int>(c) - 'A']);
		record();
		return nums;
	}
};


int main()
{
	Solution s;
	OutExpr(s.numTilePossibilities("AAB"), "%d");
	OutExpr(s.numTilePossibilities("AAABBC"), "%d");
}
