#include "leetcode.hpp"

/* 1178. 猜字谜

字谜的迷面 puzzle 按字符串形式给出，如果一个单词 word 符合下面两个条件，那么它就可以算作谜底：
	单词 word 中包含谜面 puzzle 的第一个字母。
	单词 word 中的每一个字母都可以在谜面 puzzle 中找到。
	例如，如果字谜的谜面是 "abcdefg"，那么可以作为谜底的单词有 "faced", "cabbage", 和 "baggage"；而 "beefed"（不含字母 "a"）以及 "based"（其中的 "s" 没有出现在谜面中）。

返回一个答案数组 answer，数组中的每个元素 answer[i] 是在给出的单词列表 words 中可以作为字谜迷面 puzzles[i] 所对应的谜底的单词数目。

示例：

输入：
words = ["aaaa","asas","able","ability","actt","actor","access"],
puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
输出：[1,1,3,2,4,0]
解释：
1 个单词可以作为 "aboveyz" 的谜底 : "aaaa"
1 个单词可以作为 "abrodyz" 的谜底 : "aaaa"
3 个单词可以作为 "abslute" 的谜底 : "aaaa", "asas", "able"
2 个单词可以作为 "absoryz" 的谜底 : "aaaa", "asas"
4 个单词可以作为 "actresz" 的谜底 : "aaaa", "asas", "actt", "access"
没有单词可以作为 "gaswxyz" 的谜底，因为列表中的单词都不含字母 'g'。

提示：
	1 <= words.length <= 10^5
	4 <= words[i].length <= 50
	1 <= puzzles.length <= 10^4
	puzzles[i].length == 7
	words[i][j], puzzles[i][j] 都是小写英文字母。
	每个 puzzles[i] 所包含的字符都不重复。
*/


// https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/discuss/372145/Python-Bit-manipulation-detailed-explanation
// 抄的

int getbit(string const& s)
{
	int mask = 0;
	for (char c : s)
		mask |= (1 << (c - 'a'));
	return mask;
}

vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles)
{
	unordered_map<int, int> letter_freq;
	for (string const& w : words)
	{
		int mask = getbit(w);
		letter_freq[mask] += 1;
	}

	vector<int> ans;
	ans.reserve(puzzles.size());
	for (string const& p : puzzles)
	{
		int mask = getbit(p);
		int submask = mask;
		int total = 0;
		int first_bit = p[0] - 'a';
		while (submask)
		{
			if ((submask >> first_bit) & 1)
			{
				auto it = letter_freq.find(submask);
				if (it != letter_freq.end())
					total += it->second;
			}
			submask = (submask - 1) & mask;
		}
		ans.push_back(total);
	}
	return ans;
}


int main()
{}
