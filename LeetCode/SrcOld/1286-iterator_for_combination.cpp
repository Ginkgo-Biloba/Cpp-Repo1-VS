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

// https://leetcode-cn.com/problems/iterator-for-combination/solution/er-jin-zhi-bian-ma-bu-yong-qiu-chu-quan-pai-lie-by/
// 抄的
class CombinationIterator
{
	string S;
	int len, comb, flag;

	int popcnt(int x)
	{
		// 其实 v 只有 16 位
		x = (x & UINT32_C(0x55555555)) + ((x >> 1) & UINT32_C(0x55555555));
		x = (x & UINT32_C(0x33333333)) + ((x >> 2) & UINT32_C(0x33333333));
		x = (x & UINT32_C(0x0f0f0f0f)) + ((x >> 4) & UINT32_C(0x0f0f0f0f));
		x = (x & UINT32_C(0x00ff00ff)) + ((x >> 8) & UINT32_C(0x00ff00ff));
		x = (x & UINT32_C(0x0000ffff)) + ((x >> 16) & UINT32_C(0x0000ffff));
		return x;
	}

public:
	CombinationIterator(string characters, int combinationLength)
	{
		S.swap(characters);
		len = static_cast<int>(S.size());
		sort(S.begin(), S.end());
		reverse(S.begin(), S.end());
		comb = combinationLength;
		flag = ((1 << comb) - 1) << (len - comb);
	}

	string next()
	{
		string T;
		while (flag > 0 && popcnt(flag) != comb)
			--flag;
		for (int i = 0; i < len; ++i)
		{
			if (flag & (1 << i))
				T.push_back(S[i]);
		}
		--flag;
		reverse(T.begin(), T.end());
		return T;
	}

	bool hasNext()
	{
		while (flag > 0 && popcnt(flag) != comb)
			--flag;
		return flag > 0;
	}
};


int main()
{
	CombinationIterator c("abcd", 2);
	for (int i = 0; i < 4; ++i)
		OutString(c.next());
}
