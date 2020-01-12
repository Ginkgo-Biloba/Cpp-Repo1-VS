#include "leetcode.hpp"

/* 957. N 天后的牢房

8 间牢房排成一排，每间牢房不是有人住就是空着。

每天，无论牢房是被占用或空置，都会根据以下规则进行更改：
	如果一间牢房的两个相邻的房间都被占用或都是空的，那么该牢房就会被占用。
	否则，它就会被空置。

请注意，由于监狱中的牢房排成一行，所以行中的第一个和最后一个房间无法有两个相邻的房间。

我们用以下方式描述监狱的当前状态：如果第 i 间牢房被占用，则 cell[i]==1，否则 cell[i]==0。

根据监狱的初始状态，在 N 天后返回监狱的状况（和上述 N 种变化）。

示例 1：
输入：cells = [0,1,0,1,1,0,0,1], N = 7
输出：[0,0,1,1,0,0,0,0]
解释：
下表概述了监狱每天的状况：
Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
Day 7: [0, 0, 1, 1, 0, 0, 0, 0]

示例 2：
输入：cells = [1,0,0,1,0,0,1,0], N = 1000000000
输出：[0,0,1,1,1,1,1,0]

提示：
	cells.length == 8
	cells[i] 的值为 0 或 1
	1 <= N <= 10^9
*/

int makeKey(int A[8])
{
	int x = 0;
	for (int b = 0; b < 8; ++b)
		x = (x << 1) | A[b];
	return x;
}

// 开头和结尾两个数字一次后肯定是 0
// 所以只有 6 个数字能变，那么 64 次之后肯定循环
vector<int> prisonAfterNDays(vector<int>& cells, int N)
{
	int k, A[8], B[8] = { 0 };
	int start, stop, cylen;
	std::set<int> seen;
	vector<int> keys;
	memcpy(A, cells.data(), sizeof(A));
	k = makeKey(A);
	seen.insert(k);
	keys.push_back(k);

	for (stop = 1; stop < 70; ++stop)
	{
		for (int b = 1; b < 7; ++b)
			B[b] = (A[b - 1] == A[b + 1]);
		memcpy(A, B, sizeof(A));
		k = makeKey(A);
		if (!(seen.insert(k).second))
		{
			for (start = 0; start < stop; ++start)
			{
				if (keys[start] == k)
					break;
			}
			break;
		}
		else
			keys.push_back(k);
	}

	assert(start < stop && stop < 65);
	if (N < stop)
		k = keys[N];
	else
	{
		cylen = stop - start;
		k = (N - start) % cylen + start;
		k = keys[k];
	}

	for (int b = 0; b < 8; ++b)
		cells[7 - b] = ((k >> b) & 1);
	return cells;
}


int main()
{
	vector<int>
		a = { 0, 1, 0, 1, 1, 0, 0, 1 },
		b = { 1, 0, 0, 1, 0, 0, 1, 0 };
	output(prisonAfterNDays(a, 7), "Prison Cells After N Days");
	output(prisonAfterNDays(b, 1000000000), "Prison Cells After N Days");
}
