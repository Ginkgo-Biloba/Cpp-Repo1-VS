#include "leetcode.hpp"

/* 187. Repeated DNA Sequences */


// 长度 10 两种状态用 int 足够，考虑到左移报错，用 unsigned
vector<string> findRepeatedDnaSequences(string const& str)
{
	uint32_t const mask = (1 << 20) - 1;
	uint32_t chint['T' + 1];
	chint['A'] = 0x0; chint['C'] = 0x1; chint['G'] = 0x2; chint['T'] = 0x3;
	char const intch[4] = { 'A', 'C', 'G', 'T' };

	vector<string> ans;
	uint32_t bits = 0;
	std::map<uint32_t, int> count;
	if (str.size() <= 10) return ans;

	for (size_t i = 0; i < 9; ++i)
		bits = (bits << 2) | chint[str[i]];
	for (size_t i = 9; i < str.size(); ++i)
	{
		bits = ((bits << 2) | chint[str[i]]) & mask;
		++(count[bits]);
	}

	for (auto const& elem : count)
		if (elem.second > 1)
		{
			string cur; cur.reserve(10);
			bits = elem.first;
			for (int i = 0; i < 10; ++i)
			{
				cur.push_back(intch[bits & 0x3]);
				bits >>= 2;
			}
			std::reverse(cur.begin(), cur.end());
			ans.push_back(std::move(cur));
		}

	return ans;
}




int main()
{
	string dna = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
	vector<string> ans = findRepeatedDnaSequences(dna);
	output(ans, "\n", "findRepeatedDnaSequences");
}
