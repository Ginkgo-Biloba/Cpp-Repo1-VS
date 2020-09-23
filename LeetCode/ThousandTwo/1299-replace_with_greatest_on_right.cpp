#include "leetcode.hpp"

/* 1299. 将每个元素替换为右侧最大元素

给你一个数组 arr ，请你将每个元素用它右边最大的元素替换，如果是最后一个元素，用 -1 替换。

完成所有替换操作后，请你返回这个数组。

示例：
输入：arr = [17,18,5,4,6,1]
输出：[18,6,6,6,1,-1]

提示：
	1 <= arr.length <= 10^4
	1 <= arr[i] <= 10^5
*/

vector<int> replaceElements(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	vector<int> S(len);
	S[len - 1] = -1;
	for (int i = len - 2; i >= 0; --i)
	{
		S[i] = A[i + 1];
		A[i] = max(A[i], A[i + 1]);
	}
	return S;
}


int main()
{
	vector<int>
		a = { 17, 18, 5, 4, 6, 1 },
		b = { 1, 5, 9, 6, 1, 8 };
	output(replaceElements(a));
	output(replaceElements(b));
}
