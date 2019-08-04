#include "leetcode.hpp"

string toHex(int num)
{
	std::function<void(int)> fptr;
	unsigned n = num;
	if (n == 0)
		return string("0");

	string hex;
	hex.reserve(8);
	while (n)
	{
		unsigned cur = n & 0xf;
		if (0 <= cur && cur <= 9)
			hex.push_back(static_cast<char>(cur + '0'));
		else
			hex.push_back(static_cast<char>(cur + 'a' - 10));
		n >>= 4;
	}
	std::reverse(hex.begin(), hex.end());
	return hex;
}
