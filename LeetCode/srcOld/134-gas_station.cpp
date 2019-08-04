#include "leetcode.hpp"

/* 在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
 * 你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。
 * 你从其中的一个加油站出发，开始时油箱为空。
 * 如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。
 **/

int canCompleteCircuit(vector<int> const& gas, vector<int> const& cost)
{
	int const len = static_cast<int>(gas.size());
	int start = 0, curgas = 0, idx;

	for (int i = 0; i < len + len; ++i)
	{
		idx = (i >= len) ? (i - len) : i;
		curgas += (gas[idx] - cost[idx]);
		// 不提前退出也行，因为如果能跑一圈，再多跑半圈也没事
		// if (i - start >= len) return start;
		if (curgas < 0)
		{
			if (i < len - 1)
			{
				start = i + 1;
				curgas = 0;
			}
			else return -1;
		}
	}

	return start;
}


int main()
{
	vector<int> gas = { 1, 2, 3, 4, 5 };
	vector<int> cost = { 3, 4, 5, 1, 2 };
	int ans = canCompleteCircuit(gas, cost);
	printf("%d\n", ans);
}
