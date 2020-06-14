#include "leetcode.hpp"

/* 1437. 是否所有 1 都至少相隔 k 个元素

给你一个由若干 0 和 1 组成的数组 nums 以及整数 k。

如果所有 1 都至少相隔 k 个元素，则返回 True；否则，返回 False 。

示例 1：
https://assets.leetcode.com/uploads/2020/04/15/sample_1_1791.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/03/sample_1_1791.png
输入：nums = [1,0,0,0,1,0,0,1], k = 2
输出：true
解释：每个 1 都至少相隔 2 个元素。

示例 2：
https://assets.leetcode.com/uploads/2020/04/15/sample_2_1791.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/05/03/sample_2_1791.png
输入：nums = [1,0,0,1,0,1], k = 2
输出：false
解释：第二个 1 和第三个 1 之间只隔了 1 个元素。

示例 3：
输入：nums = [1,1,1,1,1], k = 0
输出：true

示例 4：
输入：nums = [0,1,0,1], k = 1
输出：true

提示：
	1 <= nums.length <= 10^5
	0 <= k <= nums.length
	nums[i] 的值为 0 或 1
*/

bool kLengthApart(vector<int>& A, int k)
{
	int len = static_cast<int>(A.size());
	int h = 0;
	while (h < len && A[h] != 1)
		++h;
	for (int i = h + 1; i < len; ++i)
	{
		if (A[i] != 1)
			continue;
		if (h + k >= i)
			return false;
		h = i;
	}
	return true;
}


int main()
{
	vector<int>
		a = { 1, 0, 0, 0, 1, 0, 0, 1 },
		b = { 1, 0, 0, 1, 0, 1 },
		c = { 1, 1, 1, 1, 1 },
		d = { 0, 1, 0, 1 };
	OutBool(kLengthApart(a, 2));
	OutBool(kLengthApart(b, 2));
	OutBool(kLengthApart(c, 0));
	OutBool(kLengthApart(d, 1));
}
