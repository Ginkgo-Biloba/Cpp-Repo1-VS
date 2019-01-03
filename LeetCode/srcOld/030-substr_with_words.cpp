#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using std::vector;
using std::string;
using std::unordered_map;

/* You are given a string, s, and a list of words, words, that are all of the *same length*.
 * Find all starting indices of substring(s) in s that is a concatenation of each word in words
 * *exactly once* and without any intervening characters. */
vector<int> findSubStr(string const& str, vector<string> const& words)
{
	vector<int> ans;
	if (str.empty() || words.empty()) return ans;

	int s, slen = static_cast<int>(str.length());
	int w, ws = static_cast<int>(words.size()), wlen = static_cast<int>(words[0].length());
	/* hash 碰撞应该没事；如果有事，用 map */
	unordered_map<string, int> counts; // 每个单词的期望出现次数
	unordered_map<string, int> seen; // 实际看到的每个单词的次数

	for (string const& wd : words)
		counts[wd]++;
	slen -= (wlen * ws);
	for (s = 0; s <= slen; s++)
	{
		seen.clear();
		for (w = 0; w < ws; w++)
		{
			string wd = str.substr(s + w * wlen, wlen);
			if (counts.find(wd) != counts.end())
			{
				seen[wd]++;
				if (seen[wd] > counts[wd])
					break;
			}
			else break;
		}
		if (w == ws)
			ans.push_back(s);
	}

	return ans;
}

int main()
{
	/* 应该输出 0, 12*/
	string str("barfoothefoobarman");
	vector<string> words{ "foo", "bar" }; // 题目中说长度相同
	vector<int> ans = findSubStr(str, words);
	for (int const& i : ans)
		std::cout << i << "  ";
	std::cout << "\n";
	return 0;
}