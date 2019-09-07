#include "leetcode.hpp"

/* 461. 汉明距离

*/

int hammingDistance(int x, int y)
{
	unsigned v = x ^ y;
	v = (v & UINT32_C(0x55555555)) + ((v >> 1) & UINT32_C(0x55555555));
	v = (v & UINT32_C(0x33333333)) + ((v >> 2) & UINT32_C(0x33333333));
	v = (v & UINT32_C(0x0f0f0f0f)) + ((v >> 4) & UINT32_C(0x0f0f0f0f));
	v = (v & UINT32_C(0x00ff00ff)) + ((v >> 8) & UINT32_C(0x00ff00ff));
	v = (v & UINT32_C(0x0000ffff)) + ((v >> 16) & UINT32_C(0x0000ffff));
	return v;
}


int main()
{
	OutExpr(hammingDistance(1, 4), "%d");
}
