#include "leetcode.hpp"

/* 1186. 删除一次得到子数组最大和

给你一个整数数组，返回它的某个 非空 子数组（连续元素）在执行一次可选的删除操作后，所能得到的最大元素总和。

换句话说，你可以从原数组中选出一个子数组，并可以决定要不要从中删除一个元素（只能删一次哦），（删除后）子数组中至少应当有一个元素，然后该子数组（剩下）的元素总和是所有子数组之中最大的。

注意，删除一个元素后，子数组 不能为空。

请看示例：

示例 1：
输入：arr = [1,-2,0,3]
输出：4
解释：我们可以选出 [1, -2, 0, 3]，然后删掉 -2，这样得到 [1, 0, 3]，和最大。

示例 2：
输入：arr = [1,-2,-2,3]
输出：3
解释：我们直接选出 [3]，这就是最大和。

示例 3：
输入：arr = [-1,-1,-1,-1]
输出：-1
解释：
最后得到的子数组不能为空，所以我们不能选择 [-1] 并从中删去 -1 来得到 0。
我们应该直接选择 [-1]，或者选择 [-1, -1] 再从中删去一个 -1。

提示：
	1 <= arr.length <= 10^5
	-10^4 <= arr[i] <= 10^4
*/

// https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/discuss/377397/Intuitive-Java-Solution-With-Explanation
// 抄的
int maximumSum(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	vector<int> fore(len), back(len);
	int cur = 0, xval = INT_MIN;
	for (int i = 0; i < len; ++i)
	{
		if (cur < 0)
			cur = 0;
		cur += A[i];
		fore[i] = cur;
		xval = max(xval, cur);
	}
	cur = 0;
	for (int i = len - 1; i >= 0; --i)
	{
		if (cur < 0)
			cur = 0;
		cur += A[i];
		back[i] = cur;
	}
	cur = INT_MIN;
	for (int i = 1; i < len - 1; ++i)
		xval = max(xval, fore[i - 1] + back[i + 1]);
	return xval;
}


int main()
{
	vector<int>
		a = { 1, -2, 0, 3 },
		b = { 1, -2, -2, 3 },
		c = { -1, -1, -1, -1 };
	OutExpr(maximumSum(a), "%d");
	OutExpr(maximumSum(b), "%d");
	OutExpr(maximumSum(c), "%d");
}
