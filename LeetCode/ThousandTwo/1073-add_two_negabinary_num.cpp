#include "leetcode.hpp"

/* 1073. 负二进制数相加

给出基数为 -2 的两个数 arr1 和 arr2，返回两数相加的结果。

数字以 数组形式 给出：数组由若干 0 和 1 组成，按最高有效位到最低有效位的顺序排列。
例如，arr = [1,1,0,1] 表示数字 (-2)^3 + (-2)^2 + (-2)^0 = -3。
数组形式 的数字也同样不含前导零：以 arr 为例，这意味着要么 arr == [0]，要么 arr[0] == 1。

返回相同表示形式的 arr1 和 arr2 相加的结果。
两数的表示形式为：不含前导零、由若干 0 和 1 组成的数组。

示例：
输入：arr1 = [1,1,1,1,1], arr2 = [1,0,1]
输出：[1,0,0,0,0]
解释：arr1 表示 11，arr2 表示 5，输出表示 16 。

提示：
	1 <= arr1.length <= 1000
	1 <= arr2.length <= 1000
	arr1 和 arr2 都不含前导零
	arr1[i] 为 0 或 1
	arr2[i] 为 0 或 1
*/

// https://leetcode.com/problems/adding-two-negabinary-numbers/discuss/303751/C%2B%2BPython-Convert-from-Base-2-Addition
// 抄的
vector<int> addNegabinary(vector<int>& A, vector<int>& B)
{
	int a = static_cast<int>(A.size()) - 1;
	int b = static_cast<int>(B.size()) - 1;
	int carry = 0;
	vector<int> C;
	C.reserve(max(a, b) + 2);
	for (; a >= 0 || b >= 0 || carry; --a, --b)
	{
		if (a >= 0)
			carry += A[a];
		if (b >= 0)
			carry += B[b];
		C.push_back(carry & 1);
		carry = -(carry >> 1);
	}
	while (C.size() > 1 && C.back() == 0)
		C.pop_back();
	reverse(C.begin(), C.end());
	return C;
}


int main()
{
	vector<int>
		a = { 1, 1, 1, 1, 1 },
		b = { 1, 0, 1 };
	output(addNegabinary(a, b), "Adding Two Negabinary Numbers");
}
