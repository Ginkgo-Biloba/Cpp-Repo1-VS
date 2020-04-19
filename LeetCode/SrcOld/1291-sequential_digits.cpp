#include "leetcode.hpp"

/* 1291. 顺次数

我们定义「顺次数」为：每一位上的数字都比前一位上的数字大 1 的整数。

请你返回由 [low, high] 范围内所有顺次数组成的 有序 列表（从小到大排序）。

示例 1：
输出：low = 100, high = 300
输出：[123,234]

示例 2：
输出：low = 1000, high = 13000
输出：[1234,2345,3456,4567,5678,6789,12345]

提示：
	10 <= low <= high <= 10^9
*/

vector<int> sequentialDigits(int low, int high)
{
	vector<int> R;
	int digit[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int len = 1; len < 9; ++len)
		for (int i = 0; i < 9 - len; ++i)
		{
			int val = 0;
			for (int k = 0; k < len; ++k)
				val = val * 10 + digit[i + k];
			if (low <= val && val <= high)
				R.push_back(val);
		}
	return R;
}


int main()
{
	output(sequentialDigits(1, 1000000000));
}
