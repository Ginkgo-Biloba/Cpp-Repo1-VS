﻿#include "leetcode.hpp"

/* 1122. 数组的相对排序

给你两个数组，arr1 和 arr2，
	arr2 中的元素各不相同
	arr2 中的每个元素都出现在 arr1 中

对 arr1 中的元素进行排序，使 arr1 中项的相对顺序和 arr2 中的相对顺序相同。
未在 arr2 中出现过的元素需要按照升序放在 arr1 的末尾。

示例：
输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
输出：[2,2,2,1,4,3,3,9,6,7,19]

提示：
	arr1.length, arr2.length <= 1000
	0 <= arr1[i], arr2[i] <= 1000
	arr2 中的元素 arr2[i] 各不相同
	arr2 中的每个元素 arr2[i] 都出现在 arr1 中
*/

vector<int> relativeSortArray(vector<int>& A, vector<int>& B)
{
	int const val = 1001;
	vector<int> num(val);
	vector<int> C;
	for (int a : A)
		++(num[a]);

	C.reserve(A.size());
	for (int b : B)
	{
		for (int i = 0; i < num[b]; ++i)
			C.push_back(b);
		num[b] = 0;
	}

	for (int b = 0; b < val; ++b)
	{
		for (int i = 0; i < num[b]; ++i)
			C.push_back(b);
	}

	return C;
}


int main()
{}
