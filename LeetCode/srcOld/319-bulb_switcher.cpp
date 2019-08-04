#include "leetcode.hpp"

/* 319. 灯泡开关
 * 初始时有 n 个灯泡关闭。 
 * 第 1 轮，你打开所有的灯泡。 
 * 第 2 轮，每两个灯泡你关闭一次。
 * 第 3 轮，每三个灯泡切换一次开关（如果关闭则开启，如果开启则关闭）。
 * 第 i 轮，每 i 个灯泡切换一次开关。 
 * 对于第 n 轮，你只切换最后一个灯泡的开关。 找出 n 轮后有多少个亮着的灯泡。
 */

int bulbSwitch(int n)
{
	// 只有完全平方数编号的才会亮着
	// 因为其他的有偶数个因子，肯定会被切换偶数次
	int count = 0;
	for (int i = 1; i * i <= n; ++i)
		++count;	
	return count;
}

// 答案是 (int)(std::sqrt(n))...


int main()
{
	int n = bulbSwitch(3);
	printf("bulbSwitch(%d): %d\n", 3, n);
}

