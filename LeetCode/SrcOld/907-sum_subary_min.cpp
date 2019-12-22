#include "leetcode.hpp"

/* 907. 子数组的最小值之和

给定一个整数数组 A，找到 min(B) 的总和，其中 B 的范围为 A 的每个（连续）子数组。

由于答案可能很大，因此返回答案模 10^9 + 7。

示例：
输入：[3,1,2,4]
输出：17
解释：
子数组为 [3]，[1]，[2]，[4]，[3,1]，[1,2]，[2,4]，[3,1,2]，[1,2,4]，[3,1,2,4]。
最小值为 3，1，2，4，1，1，2，1，1，1，和为 17。

提示：
	1 <= A <= 30000
	1 <= A[i] <= 30000
*/

int sumSubarrayMins(vector<int>& A)
{
	int const Mod = 1e9 + 7;
	int len = static_cast<int>(A.size());
	int sum = 0;
	vector<int> L(len), R(len);
	vector<pair<int, int>> S;
	S.reserve(len);

	for (int i = 0; i < len; ++i)
	{
		sum = 1;
		while (!S.empty() && S.back().first > A[i])
		{
			sum += S.back().second;
			S.pop_back();
		}
		L[i] = sum;
		S.emplace_back(A[i], sum);
	}

	S.clear();
	for (int i = len - 1; i >= 0; --i)
	{
		sum = 1;
		// >= 处理相等的情况
		while (!S.empty() && S.back().first >= A[i])
		{
			sum += S.back().second;
			S.pop_back();
		}
		R[i] = sum;
		S.emplace_back(A[i], sum);
	}

	sum = 0;
	for (int i = 0; i < len; ++i)
		sum = (sum + A[i] * L[i] * R[i]) % Mod;
	return sum;
}


int main()
{
	vector<int> a = { 3, 1, 2, 4 };
	OutExpr(sumSubarrayMins(a), "%d");
}
