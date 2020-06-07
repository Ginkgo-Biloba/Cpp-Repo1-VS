#include "leetcode.hpp"

/* 341. 扁平化嵌套列表迭代器

给你一个嵌套的整型列表。
请你设计一个迭代器，使其能够遍历这个整型列表中的所有整数。

列表中的每一项或者为一个整数，或者是另一个列表。
其中列表的元素也可能是整数或是其他列表。

示例 1:
输入: [[1,1],2,[1,1]]
输出: [1,1,2,1,1]
解释: 通过重复调用 next 直到 hasNext 返回 false，next 返回的元素的顺序应该是: [1,1,2,1,1]。

示例 2:
输入: [1,[4,[6]]]
输出: [1,4,6]
解释: 通过重复调用 next 直到 hasNext 返回 false，next 返回的元素的顺序应该是: [1,4,6]。
*/


// This is the interface that allows for creating nested lists.
// You should not implement it, or speculate about its implementation
class NestedInteger
{
public:
	// Return true if this NestedInteger holds a single integer, rather than a nested list.
	bool isInteger() const;
	// Return the single integer that this NestedInteger holds, if it holds a single integer
	// The result is undefined if this NestedInteger holds a nested list
	int getInteger() const;
	// Return the nested list that this NestedInteger holds, if it holds a nested list
	// The result is undefined if this NestedInteger holds a single integer
	const vector<NestedInteger>& getList() const;
};

// https://leetcode-cn.com/problems/flatten-nested-list-iterator/solution/c-zong-he-ge-lu-da-lao-de-da-an-by-fxxuuu/
// 抄的
class NestedIterator
{
	vector<NestedInteger const*> S;

public:
	NestedIterator(vector<NestedInteger>& nestedList)
	{
		for (auto it = nestedList.rbegin();
			it != nestedList.rend();
			++it)
			S.push_back(&(*it));
	}

	int next()
	{
		NestedInteger const* t = S.back();
		S.pop_back();
		return t->getInteger();
	}

	bool hasNext()
	{
		while (!S.empty())
		{
			NestedInteger const* t = S.back();
			if (t->isInteger())
				return true;
			S.pop_back();
			auto& cur = t->getList();
			for (auto it = cur.rbegin(); it != cur.rend(); ++it)
				S.push_back(&(*it));
		}
		return false;
	}
};


int main()
{}
