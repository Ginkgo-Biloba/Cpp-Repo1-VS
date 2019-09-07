#include "leetcode.hpp"

/* 500. 键盘行

给定一个单词列表，只返回可以使用在键盘同一行的字母打印出来的单词。键盘如下图所示。

https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/12/keyboard.png

示例：

输入: ["Hello", "Alaska", "Dad", "Peace"]
输出: ["Alaska", "Dad"]

注意：
		你可以重复使用键盘上同一字符。
		你可以假设输入的字符串将只包含字母。
*/


static int const line[26] = {
	1, 2, 2, 1, 0, 1, 1,
	1, 0, 1, 1, 1, 2, 2,
	0, 0, 0, 0, 1, 0,
	0, 2, 0, 2, 0, 2,
};

vector<string> findWords(vector<string> const& words)
{
	vector<string> ans;
	for (string const& s : words)
	{
		size_t len = s.length();
		int L = line[tolower(s[0]) - 'a'];
		for (size_t i = 1; i < len; ++i)
			if (line[tolower(s[i]) - 'a'] != L)
			{
				L = -1;
				break;
			}
		if (L >= 0)
			ans.push_back(s);
	}
	return ans;
}


int main()
{
	vector<string> words = {
		"Hello",
		"Alaska",
		"Dad",
		"Peace"
	};
	output(findWords(words), "\n", "findWords");
}
