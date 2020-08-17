#include "leetcode.hpp"

/* 1286. 字母组合迭代器

请你设计一个迭代器类，包括以下内容：

	一个构造函数，输入参数包括：一个 有序且字符唯一 的字符串 characters（该字符串只包含小写英文字母）和一个数字 combinationLength 。
	函数 next() ，按 字典序 返回长度为 combinationLength 的下一个字母组合。
	函数 hasNext() ，只有存在长度为 combinationLength 的下一个字母组合时，才返回 True；否则，返回 False。

示例：

CombinationIterator iterator = new CombinationIterator("abc", 2); // 创建迭代器 iterator
iterator.next(); // 返回 "ab"
iterator.hasNext(); // 返回 true
iterator.next(); // 返回 "ac"
iterator.hasNext(); // 返回 true
iterator.next(); // 返回 "bc"
iterator.hasNext(); // 返回 false

提示：
	1 <= combinationLength <= characters.length <= 15
	每组测试数据最多包含 10^4 次函数调用。
	题目保证每次调用函数 next 时都存在下一个字母组合。
*/


// https://docs.python.org/3/library/itertools.html#itertools.combinations
// 抄的
class CombinationIterator
{
	// dst 存储下一个返回值，为了 O(1) 检索 next
	string src, dst;
	int len, sel;
	vector<int> idx;

public:
	CombinationIterator(string characters, int combinationLength)
	{
		src.swap(characters);
		len = static_cast<int>(src.size());
		sort(src.begin(), src.end());
		sel = combinationLength;
		idx.resize(sel);
		for (int i = 0; i < sel; ++i)
			idx[i] = i;
		dst = src.substr(0, sel);
	}

	string next()
	{
		string ans = dst;
		dst.clear();

		int i = sel - 1;
		for (; i >= 0; --i)
		{
			if (idx[i] != i + len - sel)
				break;
		}
		if (i >= 0)
		{
			idx[i] += 1;
			for (int k = i + 1; k < sel; ++k)
				idx[k] = idx[k - 1] + 1;
			for (i = 0; i < sel; ++i)
				dst.push_back(src[idx[i]]);
		}

		return ans;
	}

	bool hasNext()
	{
		return !(dst.empty());
	}
};


int main()
{
	CombinationIterator c("abcd", 2);
	for (int i = 0; i < 4; ++i)
		OutString(c.next());
}
