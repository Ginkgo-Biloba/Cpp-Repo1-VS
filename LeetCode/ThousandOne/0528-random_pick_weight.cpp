#include "leetcode.hpp"

/* 528. 按权重随机选择

给定一个正整数数组 w ，其中 w[i] 代表位置 i 的权重，请写一个函数 pickIndex ，它可以随机地获取位置 i，选取位置 i 的概率与 w[i] 成正比。

说明:
		1 <= w.length <= 10000
		1 <= w[i] <= 10^5
		pickIndex 将被调用不超过 10000 次

示例1:
输入:
["Solution","pickIndex"]
[[[1]],[]]
输出: [null,0]

示例2:
输入:
["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
[[[1,3]],[],[],[],[],[]]
输出: [null,0,1,1,1,0]

输入语法说明：
输入是两个列表：调用成员函数名和调用的参数。Solution 的构造函数有一个参数，即数组 w。pickIndex 没有参数。输入参数是一个列表，即使参数为空，也会输入一个 [] 空列表。
*/

class Solution
{
	vector<int> acml;
	double ratio;
	std::mt19937 mt;

public:
	Solution(vector<int>& w)
	{
		size_t len = w.size();
		acml.reserve(len + 1);
		acml.push_back(0);
		for (size_t i = 0; i < len; ++i)
			acml.push_back(acml[i] + w[i]);
		ratio = static_cast<double>(acml[len]) / mt.max();
		// 确保 upper_bound 不会返回 end
		++(acml[len]);
	}

	int pickIndex()
	{
		// 俄罗斯轮盘赌
		int cur = static_cast<int>(ratio * mt());
		auto it = std::upper_bound(acml.begin(), acml.end(), cur);
		cur = static_cast<int>(it - acml.begin());
		return cur - 1;
	}
};


int main()
{
	vector<int> w = { 1, 4, 3 };
	Solution s(w);
	OutExpr(s.pickIndex(), "%d");
	OutExpr(s.pickIndex(), "%d");
	OutExpr(s.pickIndex(), "%d");
	OutExpr(s.pickIndex(), "%d");
	OutExpr(s.pickIndex(), "%d");
	OutExpr(s.pickIndex(), "%d");
	OutExpr(s.pickIndex(), "%d");
	OutExpr(s.pickIndex(), "%d");
	OutExpr(s.pickIndex(), "%d");
	OutExpr(s.pickIndex(), "%d");
	OutExpr(s.pickIndex(), "%d");
}
