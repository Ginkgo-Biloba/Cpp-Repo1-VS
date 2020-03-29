#include "leetcode.hpp"

/* 1131. 绝对值表达式的最大值

给你两个长度相等的整数数组，返回下面表达式的最大值：

|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|

其中下标 i，j 满足 0 <= i, j < arr1.length。

示例 1：
输入：arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
输出：13

示例 2：
输入：arr1 = [1,-2,-5,0,10], arr2 = [0,-2,-1,-7,-4]
输出：20

提示：
	2 <= arr1.length == arr2.length <= 40000
	-10^6 <= arr1[i], arr2[i] <= 10^6
*/

// https://leetcode-cn.com/problems/maximum-of-absolute-value-expression/solution/python-jie-fa-bao-li-shu-xue-by-jiayangwu/
// 抄的
class Solution
{
public:
	int maxAbsValExpr(vector<int>& A, vector<int>& B)
	{
		int len = static_cast<int>(A.size());
		int m[4] = { INT_MAX, INT_MAX, INT_MAX, INT_MAX };
		int n[4] = { INT_MIN, INT_MIN, INT_MIN, INT_MIN };
		int v[4];
		for (int i = 0; i < len; ++i)
		{
			v[0] = A[i] + B[i] + i;
			v[1] = A[i] + B[i] - i;
			v[2] = A[i] - B[i] + i;
			v[3] = A[i] - B[i] - i;
			for (int k = 0; k < 4; ++k)
			{
				m[k] = min(m[k], v[k]);
				n[k] = max(n[k], v[k]);
			}
		}
		v[0] = INT_MIN;
		for (int k = 0; k < 4; ++k)
			v[0] = max(v[0], n[k] - m[k]);
		return v[0];
	}
};


int main()
{}
