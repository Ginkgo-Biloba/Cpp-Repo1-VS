#include "leetcode.hpp"

/* 228. 汇总区间

给定一个无重复元素的有序整数数组，返回数组区间范围的汇总。

示例 1:
输入: [0,1,2,4,5,7]
输出: ["0->2","4->5","7"]
解释: 0,1,2 可组成一个连续的区间; 4,5 可组成一个连续的区间。

示例 2:
输入: [0,2,3,4,6,8,9]
输出: ["0","2->4","6","8->9"]
解释: 2,3,4 可组成一个连续的区间; 8,9 可组成一个连续的区间。
*/

vector<string> summaryRanges(vector<int>& A)
{
	char buf[32];
	vector<string> R;
	int len = static_cast<int>(A.size());
	for (int i = 0; i < len;)
	{
		int k = i + 1;
		for (; k < len; ++k)
		{
			if (A[k - 1] + 1 != A[k])
				break;
		}
		if (i + 1 == k)
			sprintf(buf, "%d", A[i]);
		else
			sprintf(buf, "%d->%d", A[i], A[k - 1]);
		R.emplace_back(buf);
		i = k;
	}
	return R;
}


int main()
{
	vector<int>
		a = { 0, 1, 2, 4, 5, 7 },
		b = { 0, 2, 3, 4, 6, 8, 9 };
	output(summaryRanges(a), ",", "Summary Ranges");
	output(summaryRanges(b), ",", "Summary Ranges");
}
