#include "leetcode.hpp"

/* 135. 分发糖果

老师想给孩子们分发糖果，有 N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。

你需要按照以下要求，帮助老师给这些孩子分发糖果：
	每个孩子至少分配到 1 个糖果。
	相邻的孩子中，评分高的孩子必须获得更多的糖果。

那么这样下来，老师至少需要准备多少颗糖果呢？

示例 1:
输入: [1,0,2]
输出: 5
解释: 你可以分别给这三个孩子分发 2、1、2 颗糖果。

示例 2:
输入: [1,2,2]
输出: 4
解释:
你可以分别给这三个孩子分发 1、2、1 颗糖果。
第三个孩子只得到 1 颗糖果，这已满足上述两个条件。
*/

int candy(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	int sum = 0;
	vector<int> L(len), R(len);
	for (int i = 0; i < len;)
	{
		int k = i + 1;
		L[i] = 1;
		while ((k < len) && (A[k - 1] < A[k]))
		{
			L[k] = k - i + 1;
			++k;
		}
		i = k;
	}
	for (int i = len - 1; i >= 0;)
	{
		int k = i - 1;
		R[i] = 1;
		while ((k >= 0) && (A[k] > A[k + 1]))
		{
			R[k] = i - k + 1;
			--k;
		}
		i = k;
	}
	for (int i = 0; i < len; ++i)
		sum += max(L[i], R[i]);
	return sum;
}


int main()
{
	vector<int>
		a = { 1, 0, 2 },
		b = { 1, 2, 2 };
	OutExpr(candy(a), "%d");
	OutExpr(candy(b), "%d");
}
