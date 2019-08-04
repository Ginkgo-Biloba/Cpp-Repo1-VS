#include "leetcode.hpp"


// https://leetcode.com/problems/number-of-digit-one/discuss/64382/JavaPython-one-pass-solution-easy-to-understand
// 抄的
int countDigitOne(int n)
{
	int64_t q = n, x = 1;
	int ans = 0;

	while(q > 0)
	{
		int digit = q % 10;
		q /= 10;
		ans += q * x;
		if (digit == 1) ans += n % x + 1;
		else if (digit >  1) ans += x;
		x *= 10;
	}

	return ans;
}



int main()
{
	int ans = countDigitOne(12345);
	printf("countDigitOne: %d\n", ans);
}

