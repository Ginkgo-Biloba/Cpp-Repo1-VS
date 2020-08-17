#include "leetcode.hpp"

/* 769. 最多能完成排序的块

数组arr是[0, 1, ..., arr.length - 1]的一种排列，我们将这个数组分割成几个“块”，并将这些块分别进行排序。
之后再连接起来，使得连接的结果和按升序排序后的原数组相同。

我们最多能将数组分成多少块？

示例 1:
输入: arr = [4,3,2,1,0]
输出: 1
解释:
将数组分成2块或者更多块，都无法得到所需的结果。
例如，分成 [4, 3], [2, 1, 0] 的结果是 [3, 4, 0, 1, 2]，这不是有序的数组。

示例 2:
输入: arr = [1,0,2,3,4]
输出: 4
解释:
我们可以把它分成两块，例如 [1, 0], [2, 3, 4]。
然而，分成 [1, 0], [2], [3], [4] 可以得到最多的块数。

注意:
	arr 的长度在 [1, 10] 之间。
	arr[i]是 [0, 1, ..., arr.length - 1]的一种排列。
*/

// https://leetcode.com/problems/max-chunks-to-make-sorted/discuss/113528/Simple-Java-O(n)-Solution-with-detailed-explanation
// 抄的
int maxChunksToSorted(vector<int>& arr)
{
	int len = static_cast<int>(arr.size());
	int ans = 0, cur = INT_MIN;
	for (int i = 0; i < len; ++i)
	{
		cur = std::max(cur, arr[i]);
		if (i == cur)
			++ans;
	}
	return ans;
}


/* 768. 最多能完成排序的块 II

这个问题和“最多能完成排序的块”相似，但给定数组中的元素可以重复，输入数组最大长度为2000，其中的元素最大为10**8。

arr是一个可能包含重复元素的整数数组，我们将这个数组分割成几个“块”，并将这些块分别进行排序。之后再连接起来，使得连接的结果和按升序排序后的原数组相同。

我们最多能将数组分成多少块？

示例 1:
输入: arr = [5,4,3,2,1]
输出: 1
解释:
将数组分成2块或者更多块，都无法得到所需的结果。
例如，分成 [5, 4], [3, 2, 1] 的结果是 [4, 5, 1, 2, 3]，这不是有序的数组。

示例 2:
输入: arr = [2,1,3,4,4]
输出: 4
解释:
我们可以把它分成两块，例如 [2, 1], [3, 4, 4]。
然而，分成 [2, 1], [3], [4], [4] 可以得到最多的块数。

注意:
	arr的长度在[1, 2000]之间。
	arr[i]的大小在[0, 10**8]之间。
*/

// https://leetcode.com/problems/max-chunks-to-make-sorted-ii/discuss/113462/Java-solution-left-max-and-right-min.
// 抄的
int maxChunksToSorted2(vector<int>& arr)
{
	int len = static_cast<int>(arr.size());
	int ans = 0;
	vector<int> Lmax = arr, Rmin = arr;

	for (int i = 1; i < len; ++i)
		Lmax[i] = std::max(Lmax[i - 1], Lmax[i]);
	for (int i = len - 2; i >= 0; --i)
		Rmin[i] = std::min(Rmin[i], Rmin[i + 1]);
	for (int i = 1; i < len; ++i)
	{
		if (Lmax[i - 1] <= Rmin[i])
			++ans;
	}

	return ans + 1;
}

// https://leetcode.com/problems/max-chunks-to-make-sorted-ii/discuss/113464/C%2B%2B-9-lines-15ms
int maxChunksToSorted3(vector<int>& arr)
{
	int len = static_cast<int>(arr.size());
	vector<int> num = arr;
	int64_t s0 = 0, s1 = 0;
	int ans = 0;
	sort(num.begin(), num.end());
	for (int i = 0; i < len; ++i)
	{
		s0 += arr[i];
		s1 += num[i];
		if (s0 == s1)
			++ans;
	}
	return ans;
}


int main()
{
	vector<int>
		n1 = { 4, 3, 2, 1, 0 },
		n2 = { 1, 0, 2, 3, 4 },
		n3 = { 5, 4, 3, 2, 1 },
		n4 = { 2, 1, 3, 4, 4 },
		n5 = { 1, 1, 0, 0, 1 };

	OutExpr(maxChunksToSorted(n1), "%d");
	OutExpr(maxChunksToSorted(n2), "%d");
	OutExpr(maxChunksToSorted2(n3), "%d");
	OutExpr(maxChunksToSorted2(n4), "%d");
	OutExpr(maxChunksToSorted2(n5), "%d");
}
