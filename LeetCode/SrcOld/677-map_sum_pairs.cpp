#include "leetcode.hpp"

/* 677. 键值映射

实现一个 MapSum 类里的两个方法，insert 和 sum。
对于方法 insert，你将得到一对（字符串，整数）的键值对。
字符串表示键，整数表示值。如果键已经存在，那么原来的键值对将被替代成新的键值对。
对于方法 sum，你将得到一个表示前缀的字符串，你需要返回所有以该前缀开头的键的值的总和。

示例 1:
输入: insert("apple", 3), 输出: Null
输入: sum("ap"), 输出: 3
输入: insert("app", 2), 输出: Null
输入: sum("ap"), 输出: 5
*/

// https://leetcode.com/problems/map-sum-pairs/discuss/107520/C%2B%2B-Easy-solution-ordered-map
// 抄的
class MapSum
{
	std::map<string, int> m;

public:
	/** Initialize your data structure here. */
	MapSum() {}

	void insert(string key, int val)
	{
		m[key] = val;
	}

	int sum(string prefix)
	{
		int s = 0;
		size_t len = prefix.size();
		auto it = m.lower_bound(prefix);
		auto itend = m.end();
		for (; it != itend && it->first.substr(0, len) == prefix; ++it)
			s += it->second;
		return s;
	}
};


int main()
{
	vector<string> dict = { "hello", "leetcode" };
	MapSum m;
	m.insert("apple", 3);
	OutExpr(m.sum("ap"), "%d");
	m.insert("app", 2);
	OutExpr(m.sum("ap"), "%d");
}
