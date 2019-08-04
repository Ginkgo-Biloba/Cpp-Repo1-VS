#include "leetcode.hpp"

#include <nmmintrin.h>

/* 372. 超级次方

你的任务是计算 a^b 对 1337 取模。
a 是一个正整数，b 是一个非常大的正整数且会以数组形式给出。

示例 1:
输入: a = 2, b = [3]
输出: 8

示例 2:
输入: a = 2, b = [1,0]
输出: 1024
*/

// 抄的
int superPow(int _a, vector<int>& _b)
{
	size_t len = _b.size();
	if (len == 0)
		return 1;
	uint64_t const div = 1337;
	uint64_t a = _a;
	uint64_t amod[10] = { 1 }; // a^[0,9] 对 div 的余数
	for (int i = 1; i < 10; ++i)
		amod[i] = (amod[i - 1] * a) % div;

	uint64_t d = amod[_b[0]]; // 答案
	for (size_t i = 1; i < len; ++i)
	{
		uint64_t t = d;
		for (int k = 1; k < 10; ++k)
			t = t * d % div;
		d = t * amod[_b[i]] % div;
	}

	int _d = static_cast<int>(d);
	return _d;
}


int main()
{
	int a = 2;
	vector<int> b = {1, 0, 0};
	OutExpr(superPow(a, b), "%d");
}
