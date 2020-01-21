#include "leetcode.hpp"

/* 1054. 距离相等的条形码

在一个仓库里，有一排条形码，其中第 i 个条形码为 barcodes[i]。

请你重新排列这些条形码，使其中两个相邻的条形码不能相等。
你可以返回任何满足该要求的答案，此题保证存在答案。

示例 1：
输入：[1,1,1,2,2,2]
输出：[2,1,2,1,2,1]

示例 2：
输入：[1,1,1,1,2,2,3,3]
输出：[1,3,1,3,2,1,2,1]

提示：
	1 <= barcodes.length <= 10000
	1 <= barcodes[i] <= 10000
*/


vector<int> rearrangeBarcodes(vector<int>& barcodes)
{
	int const upper = 10001;
	int len = static_cast<int>(barcodes.size());
	int pos = 0, offset = 1;
	vector<int> num(upper);
	vector<pair<int, int>> val;
	num.reserve(barcodes.size());
	val.reserve(barcodes.size());
	for (int b : barcodes)
		num[b] += 1;
	for (int i = 1; i < upper; ++i)
	{
		if (num[i] > 0)
			val.emplace_back(-num[i], i);
	}
	num.resize(len);
	sort(val.begin(), val.end());
	for (pair<int, int> it : val)
		for (; it.first < 0; ++(it.first))
		{
			num[pos] = it.second;
			pos += 2;
			if (pos >= len)
			{
				pos = offset;
				++offset;
			}
		}
	return num;
}


int main()
{
	vector<int>
		a = { 1, 1, 1, 2, 2, 2 },
		b = { 1, 1, 1, 1, 2, 2, 3, 3 },
		c = { 1, 1, 2 };
	output(rearrangeBarcodes(a), "Distant Barcodes");
	output(rearrangeBarcodes(b), "Distant Barcodes");
	output(rearrangeBarcodes(c), "Distant Barcodes");
}
