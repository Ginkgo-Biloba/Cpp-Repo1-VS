#include "leetcode.hpp"

/* 676. 实现一个魔法字典

实现一个带有buildDict, 以及 search方法的魔法字典。

对于buildDict方法，你将被给定一串不重复的单词来构建一个字典。

对于search方法，你将被给定一个单词，并且判定能否只将这个单词中一个字母换成另一个字母，使得所形成的新单词存在于你构建的字典中。

示例 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False

注意:
	你可以假设所有输入都是小写字母 a-z。
	为了便于竞赛，测试所用的数据量很小。你可以在竞赛结束后，考虑更高效的算法。
	请记住重置MagicDictionary类中声明的类变量，因为静态/类变量会在多个测试用例中保留。 请参阅这里了解更多详情。
*/

// https://leetcode.com/problems/implement-magic-dictionary/discuss/107446/Easy-14-lines-Java-solution-HashMap/109620
// 抄的
class MagicDictionary
{
	unordered_map<string, char> um;

public:
	/** Initialize your data structure here. */
	MagicDictionary() {}

	/** Build a dictionary through a list of words */
	void buildDict(vector<string> const& dict)
	{
		um.clear();
		for (string const& word : dict)
		{
			string key = word;
			size_t len = word.size();
			for (size_t i = 0; i < len; ++i)
			{
				key[i] = '0';
				if (um.find(key) == um.end())
					um[key] = word[i];
				// 比如 hes 和 his，输入 his 的时候应该返回 true
				// 所以不应该是 '0' 和 word[i]
				else if (um[key] != word[i])
					um[key] = 0;
				key[i] = word[i];
			}
		}
	}

	/** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
	bool search(string const& word)
	{
		string key = word;
		size_t len = word.size();
		for (size_t i = 0; i < len; ++i)
		{
			key[i] = '0';
			if (um.find(key) != um.end() && um[key] != word[i])
				return true;
			key[i] = word[i];
		}
		return false;
	}
};


int main()
{
	vector<string> dict = { "hello", "leetcode" };
	MagicDictionary md;
	md.buildDict(dict);
	OutExpr(boolstr[md.search("hello")], "%s");
	OutExpr(boolstr[md.search("hhllo")], "%s");
	OutExpr(boolstr[md.search("hell")], "%s");
	OutExpr(boolstr[md.search("leetcoded")], "%s");
}
