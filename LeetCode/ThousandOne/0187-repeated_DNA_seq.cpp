#include "leetcode.hpp"

/* 187. 重复的DNA序列

所有 DNA 都由一系列缩写为 A，C，G 和 T 的核苷酸组成，例如：“ACGAATTCCG”。在研究 DNA 时，识别 DNA 中的重复序列有时会对研究非常有帮助。

编写一个函数来查找 DNA 分子中所有出现超过一次的 10 个字母长的序列（子串）。

示例：
输入：s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
输出：["AAAAACCCCC", "CCCCCAAAAA"]
*/

vector<string> findRepeatedDnaSequences(string s)
{
	vector<string> R;
	int len = static_cast<int>(s.length());
	if (len < 10)
		return R;
	unordered_map<int, int> exist;
	int cur = 0, mask = (1 << 20) - 1;
	char c2i[128] = { 0 };
	c2i['A'] = 0b01;
	c2i['C'] = 0b10;
	c2i['G'] = 0b11;
	for (int i = 0; i < 9; ++i)
		cur = (cur << 2) | c2i[s[i]];
	for (int i = 9; i < len; ++i)
	{
		cur = ((cur << 2) | c2i[s[i]]) & mask;
		exist[cur] += 1;
		if (exist[cur] == 2)
			R.push_back(s.substr(i - 9, 10));
	}
	return R;
}


int main()
{
	output(
		findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"),
		", ", "DNA");
	output(
		findRepeatedDnaSequences("AAAAAAAAAAAAAAA"),
		", ", "DNA");
}
