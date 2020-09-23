#include "leetcode.hpp"

/* 372. 超级次方

你的任务是计算 ab 对 1337 取模，a 是一个正整数，b 是一个非常大的正整数且会以数组形式给出。

示例 1:
输入: a = 2, b = [3]
输出: 8

示例 2:
输入: a = 2, b = [1,0]
输出: 1024
*/

int superPow(int a, vector<int>& b)
{
	int const m = 1337;
	int len = static_cast<int>(b.size());
	int r = 1, t = a % m;
	vector<int> p(10, 1);
	for (int i = 1; i < 10; ++i)
		p[i] = p[i - 1] * t % m;
	for (int i = 0; i < len; ++i)
	{
		// a^(10*x+y) = ((a^x)^10)*(a^b)
		/*t = 1;
		for (int k = 0; k < 10; ++k)
			t = (t * r) % m;*/
		int p2 = (r * r) % m;
		int p4 = (p2 * p2) % m;
		t = ((p4 * p4) % m) * p2 % m;
		r = (t * p[b[i]]) % m;
	}
	return r;
}


int main()
{
	vector<int>
		a = { 3 },
		b = { 1, 0 },
		c = { 1, 2, 3 };
	OutExpr(superPow(2, a), "%d");
	OutExpr(superPow(2, b), "%d");
	OutExpr(superPow(2, c), "%d");
}
