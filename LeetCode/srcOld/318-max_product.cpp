#include "../srcOld/utility.hpp"

/* 318. 最大单词长度乘积
 * 给定一个字符串数组 words，找到 length(word[i]) * length(word[j]) 的最大值，
 * 并且这两个单词不含有公共字母。
 * 你可以认为每个单词只包含小写字母。如果不存在这样的两个单词，返回 0。
 */

static inline
int times(unsigned xmask, int xlen, unsigned ymask, int ylen)
{
	return (xmask & ymask) ? 0 : (xlen * ylen);
}

int maxProduct(vector<string>& words)
{
	int ans = 0;
	size_t const nword = words.size();
	if (nword < 2) return 0;
	
	vector<int> lens; lens.reserve(nword);
	vector<unsigned> masks; masks.reserve(nword);
	for (size_t i = 0; i < nword; ++i)
	{
		int wlen = static_cast<int>(words[i].size());
		lens.push_back(wlen);
		char const* ptr = words[i].data();
		unsigned cur = 0;
		for (int w = 0; w < wlen; ++w)
			cur |= (1u << (ptr[w] - 'a'));
		masks.push_back(cur);
	}

	for (size_t i = 0; i < nword; ++i)
		for (size_t k = i + 1; k < nword; ++k)
		{
			int cur = times(masks[i], lens[i], masks[k], lens[k]);
			if (ans < cur) ans = cur;
		}

	return ans;
}


int main()
{
	vector<string> words = { "abcw", "baz", "foo", "bar", "xtfn", "abcdef" };
	int n = maxProduct(words);
	printf("maxProduct: %d\n", n);
}

