#include "leetcode.hpp"

/* 1345. 跳跃游戏 IV

给你一个整数数组 arr ，你一开始在数组的第一个元素处（下标为 0）。

每一步，你可以从下标 i 跳到下标：
	i + 1 满足：i + 1 < arr.length
	i - 1 满足：i - 1 >= 0
	j 满足：arr[i] == arr[j] 且 i != j

请你返回到达数组最后一个元素的下标处所需的最少操作次数 。

注意：任何时候你都不能跳到数组外面。

示例 1：
输入：arr = [100,-23,-23,404,100,23,23,23,3,404]
输出：3
解释：那你需要跳跃 3 次，下标依次为 0 --> 4 --> 3 --> 9 。下标 9 为数组的最后一个元素的下标。

示例 2：
输入：arr = [7]
输出：0
解释：一开始就在最后一个元素处，所以你不需要跳跃。

示例 3：
输入：arr = [7,6,9,6,9,6,9,7]
输出：1
解释：你可以直接从下标 0 处跳到下标 7 处，也就是数组的最后一个元素处。

示例 4：
输入：arr = [6,1,9]
输出：2

示例 5：
输入：arr = [11,22,7,7,7,7,7,7,7,22,13]
输出：3

提示：
	1 <= arr.length <= 5 * 10^4
	-10^8 <= arr[i] <= 10^8
*/

int minJumps(vector<int>& A)
{
	int len = static_cast<int>(A.size());
	if (len < 2)
		return len - 1;
	vector<char> visit(len);
	unordered_map<int, vector<int>> M;
	for (int i = 0; i < len; ++i)
		M[A[i]].push_back(i);
	vector<int> current, nextloop;
	current.push_back(0);
	visit[0] = 1;
	for (int step = 1; !current.empty(); ++step)
	{
		nextloop.clear();
		for (int i : current)
		{
			if (i > 0 && !visit[i - 1])
			{
				nextloop.push_back(i - 1);
				visit[i - 1] = 1;
			}
			if (i < len - 1 && !visit[i + 1])
			{
				nextloop.push_back(i + 1);
				visit[i + 1] = 1;
			}
			vector<int>& v = M[A[i]];
			for (int k : v)
				if (!visit[k])
				{
					nextloop.push_back(k);
					visit[k] = 1;
				}
			v.clear();
		}
		if (visit[len - 1])
			return step;
		nextloop.swap(current);
	}
	return -1;
}


int main()
{
	vector<int>
		a = { 100, -23, -23, 404, 100, 23, 23, 23, 3, 404 },
		b = { 7 },
		c = { 7, 6, 9, 6, 9, 6, 9, 7 },
		d = { 6, 1, 9 },
		e = { 11, 22, 7, 7, 7, 7, 7, 7, 7, 22, 13 };
	OutExpr(minJumps(a), "%d");
	OutExpr(minJumps(b), "%d");
	OutExpr(minJumps(c), "%d");
	OutExpr(minJumps(d), "%d");
	OutExpr(minJumps(e), "%d");
}
