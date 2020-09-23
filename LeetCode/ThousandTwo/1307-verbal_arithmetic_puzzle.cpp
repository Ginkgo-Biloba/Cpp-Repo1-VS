#include "leetcode.hpp"

/* 1307. 口算难题

给你一个方程，左边用 words 表示，右边用 result 表示。

你需要根据以下规则检查方程是否可解：
	每个字符都会被解码成一位数字（0 - 9）。
	每对不同的字符必须映射到不同的数字。
	每个 words[i] 和 result 都会被解码成一个没有前导零的数字。
	左侧数字之和（words）等于右侧数字（result）。

如果方程可解，返回 True，否则返回 False。

示例 1：
输入：words = ["SEND","MORE"], result = "MONEY"
输出：true
解释：映射 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
所以 "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652

示例 2：
输入：words = ["SIX","SEVEN","SEVEN"], result = "TWENTY"
输出：true
解释：映射 'S'-> 6, 'I'->5, 'X'->0, 'E'->8, 'V'->7, 'N'->2, 'T'->1, 'W'->'3', 'Y'->4
所以 "SIX" + "SEVEN" + "SEVEN" = "TWENTY" ,  650 + 68782 + 68782 = 138214

示例 3：
输入：words = ["THIS","IS","TOO"], result = "FUNNY"
输出：true

示例 4：
输入：words = ["LEET","CODE"], result = "POINT"
输出：false

提示：
	2 <= words.length <= 5
	1 <= words[i].length, results.length <= 7
	words[i], result 只含有大写英文字母
	表达式中使用的不同字符数最大为 10
*/

class SolutionFailed
{
	int maptab[128];
	char forbid[128]; // -1 不存在 0 存在允许 1 不允许
	string turn, source;

	int str2int(string const& s)
	{
		int n = 0;
		for (char c : s)
			n = n * 10 + maptab[c];
		return n;
	}

public:
	bool isSolvable(vector<string>& words, string result)
	{
		for (int i = 0; i < 128; ++i)
			maptab[i] = forbid[i] = -1;
		turn.clear();
		turn.reserve(12);
		unordered_set<char> allchar;
		vector<size_t> wlen;
		for (string const& w : words)
		{
			for (char c : w)
				allchar.insert(c);
			wlen.push_back(w.size());
		}
		for (char c : result)
			allchar.insert(c);
		for (size_t w : wlen)
		{
			if (w > result.size())
				return false;
		}

		for (char c : allchar)
		{
			forbid[c] = 0; // 存在
			turn.push_back(c);
			maptab[c] = 0;
		}
		source = turn;

		// 禁止
		for (string const& w : words)
			forbid[w[0]] = 1;
		forbid[result[0]] = 1;
		// 占位符号，强制 10 个字符，以区分各种可能
		while (turn.size() != 10)
			turn.push_back('.');
		forbid['.'] = 1;

		sort(turn.begin(), turn.end());
		for (bool run = true; run;)
		{
			if (forbid[turn[0]] > 0)
			{
				char cand = turn[0];
				for (++cand; cand <= 'Z'; ++cand)
				{
					if (forbid[cand] == 0)
						break;
				}
				if (cand > 'Z')
					run = false;
				else
				{
					int i = 1;
					turn[0] = cand;
					for (char c : source)
						if (cand != c)
						{
							turn[i] = c;
							++i;
						}
					for (; i < 10; ++i)
						turn[i] = '.';
					sort(turn.begin() + 1, turn.end());
				}
				continue;
			}
			for (int i = 0; i < 10; ++i)
				maptab[turn[i]] = i;
			int sum = str2int(result);
			for (string const& w : words)
			{
				sum -= str2int(w);
				if (sum < 0)
					break;
			}
			if (sum == 0)
				return true;
			run = next_permutation(turn.begin(), turn.end());
		}
		return false;
	}
};


// https://leetcode.com/problems/verbal-arithmetic-puzzle/discuss/463916/C++-12ms-DFS-and-Backtracking-and-Prunning-Strategy/416383
// 抄的
class Solution
{
	int c2i[128];
	char i2c[10];
	vector<string> words;
	string result;

	bool dfs(int index, int l, int s)
	{
		// index is the current word index in words
		// eg. words[index], for index from 0~words.length()-1
		// l is the current digit for the word and result
		// eg. words[index][l], result[l] for l from 0~result.length()-1 or l from 0~words[index].length()-1
		// s is the accumulated sum for those words[index] at digit l; so s%10 is the final result of current digit, s/10 is the carry

		// if we reach the end of result we have to check if there is no carry
		if (l == static_cast<int>(result.size()))
			return s == 0;

		// if we traverse the digit for all the words, we will go to next digit
		if (index == static_cast<int>(words.size()))
		{
			// if the character in the result at digit l has been used
			if (c2i[result[l]] != -1)
			{
				// we check if the digit matches to s%10 (the accumulated sum of current digit mod by 10)
				// we start from words[0] of next digit, and pass on the carry value
				if (c2i[result[l]] == s % 10)
					return dfs(0, l + 1, s / 10);
			}
			// we check if the digit for the accumulated sum has not been used
			else if (i2c[s % 10] == -1)
			{
				// the leading digit must not be 0
				if ((l == static_cast<int>(result.size()) - 1)
					&& (s % 10 == 0))
					return false;
				// map the character in result to the accumulated sum of current digit
				c2i[result[l]] = s % 10;
				// map the accumulated sum of current digit to the character in result
				i2c[s % 10] = result[l];
				// store the result here for backtracking instead of directly return the result (because we have to undo the previous 2 operations), note that we start from words[0] at next digit, and pass on the carry (s/10)
				bool t = dfs(0, l + 1, s / 10);
				// undo the operation (part of backtracking)
				c2i[result[l]] = -1;
				i2c[s % 10] = -1;
				return t;
			}
			// if we didn't go to above "if" or "else if", then the result must be false
			return false;
		}

		string const& wd = words[index];
		// if the current digit is larger than the current length of words[index], we just skip the word
		// go to word[index+1] at the same digit, the sum s will not be updated since we skip the word
		if (l >= static_cast<int>(wd.size()))
			return dfs(index + 1, l, s);

		// if the character has already been used
		if (c2i[wd[l]] != -1)
		{
			// prevent that the leading digit is 0
			// we will add the digit corresponding to the character to result s, and go to word[index+1]
			if ((l != static_cast<int>(wd.size()) - 1)
				|| (c2i[wd[l]] != 0))
				return dfs(index + 1, l, s + c2i[wd[l]]);
		}

		// if the character has not been used, and the current digit does not reach the end of the word
		for (int i = 0; i < 10; ++i)
		{
			// if the digit has been used, we can't use it again
			if (i2c[i] != -1)
				continue;

			// the leading digit of word[index] must not be 0
			if ((i == 0) && (l == static_cast<int>(wd.size()) - 1))
				continue;

			i2c[i] = wd[l];
			c2i[wd[l]] = i;
			bool t = dfs(index + 1, l, s + i);
			i2c[i] = -1;
			c2i[wd[l]] = -1;
			if (t)
				return true;
		}

		// if all of above fails, return false
		return false;
	}

public:
	bool isSolvable(vector<string>& _words, string _result)
	{
		words.swap(_words);
		result.swap(_result);

		for (string& w : words)
		{
			// the length of all words must not be longer than the length of result
			if (w.size() > result.size())
				return false;
			// reverse all the words, so that we can calculate the current digit and pass on the carry more intuitionally
			reverse(w.begin(), w.end());
		}
		reverse(result.begin(), result.end());

		memset(c2i, 0xff, sizeof(c2i));
		memset(i2c, 0xff, sizeof(i2c));
		// we start from words[0] at digit 0 (the least significant digit in this case)
		// and the initial sum is 0
		bool t = dfs(0, 0, 0);
		return t;
	}
};


int main()
{
	vector<string>
		a = { "SEND", "MORE" },
		b = { "SIX", "SEVEN", "SEVEN" },
		c = { "THIS", "IS", "TOO" },
		d = { "LEET", "CODE" };
	Solution s;
	OutBool(s.isSolvable(a, "MONEY"));
	OutBool(s.isSolvable(b, "TWENTY"));
	OutBool(s.isSolvable(c, "FUNNY"));
	OutBool(s.isSolvable(d, "POINT"));
}
