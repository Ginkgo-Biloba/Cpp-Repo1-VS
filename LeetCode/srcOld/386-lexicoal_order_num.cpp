#include "../srcOld/utility.hpp"

/* 386. 字典序排数

给定一个整数 n, 返回从 1 到 n 的字典顺序。

例如，给定 n =1 3，返回 [1,10,11,12,13,2,3,4,5,6,7,8,9] 。

请尽可能的优化算法的时间复杂度和空间复杂度。
输入的数据 n 小于等于 5,000,000。
*/

// https://leetcode.com/problems/lexicographical-numbers/discuss/86242/Java-O(n)-time-O(1)-space-iterative-solution-130ms
// 抄的
vector<int> lexicalOrder(int n)
{
	vector<int> ans;
	int i, cur = 1;
	for (i = 1; i <= n; i++)
	{
		ans.push_back(cur);
		if (cur * 10 <= n)
			cur *= 10;
		else if (cur % 10 != 9 && cur < n)
			cur++;
		else
		{
			cur /= 10;
			while (cur % 10 == 9)
				cur /= 10;
			cur++;
		}
	}
	return ans;
}


int main()
{
	vector<int> d = lexicalOrder(14);
	output(d, "lexicalOrder");
}
