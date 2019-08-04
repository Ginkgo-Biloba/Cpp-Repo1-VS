#include "leetcode.hpp"

/* 343. 整数拆分

给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

示例 1:
输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。

示例 2:
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。

说明: 你可以假设 n 不小于 2 且不大于 58。
*/

// https://leetcode.com/problems/integer-break/discuss/246283/easy-step-by-step-interview-thought-process-with-recursion-solution
// https://leetcode.com/problems/integer-break/discuss/80721/Why-factor-2-or-3-The-math-behind-this-problem.
// 上面是通用的参考
// https://leetcode.com/problems/integer-break/discuss/80689/A-simple-explanation-of-the-math-part-and-a-O(n)-solution
// 抄的
int integerBreak(int n)
{
	if (n == 2) return 1;
	if (n == 3) return 2;
	int p = 1;
	while (n > 4)
	{
		p *= 3;
		n -= 3;
	}
	p *= n;
	return p;
}


int main()
{
	int n = integerBreak(10);
	printf("integerBreak: %d\n", n);
}
