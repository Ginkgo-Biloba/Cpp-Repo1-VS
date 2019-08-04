#include "leetcode.hpp"

/* Given a non-negative integer num,
 * repeatedly add all its digits until the result has only one digit.
 */

 // https://leetcode.com/problems/add-digits/discuss/68572/3-methods-for-python-with-explains
 // 抄的
int addDigits(int num)
{
	int ans = (num - 1) % 9 + 1;
	return ans;
}



