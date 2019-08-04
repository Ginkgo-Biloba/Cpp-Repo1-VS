#include "leetcode.hpp"

/* 338. Counting Bits
popcnt for [0, n]
*/


vector<int> countBits(int num)
{
	vector<int> bits(num + 1);
	bits[0] = 0;
	for (int i = 1; i <= num; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	return bits;
}


int main()
{
	vector<int> bits = countBits(16);
	output(bits, "countBits");
}
