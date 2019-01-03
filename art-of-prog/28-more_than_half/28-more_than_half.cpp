#include <cstdio>
#include <cstdlib>
#include <ctime>

/**< 问题：一个数组中有很多数，我们要找出其中那个出现次数超过总数一半的数字 */
// Ref: http://taop.marchtea.com/04.03.html
/* 考虑到这个问题本身的特殊性，我们可以在遍历数组的时候保存两个值：
 * 1 candidate，用来保存数组中遍历到的某个数字
 * 2 nTimes，表示当前数字的出现次数，初始化为 1
 * 当我们遍历到数组中下一个数字的时候：
 * - 如果下一个数字与之前 candidate 保存的数字相同，则 nTimes 加 1；
 * - 如果下一个数字与之前 candidate 保存的数字不同，则 nTimes 减 1；
 * - 每当出现次数 nTimes 变为 0 后，用 candidate 保存下一个数字，并把 nTimes 重新设为1
 * - 最后返回的就是最后一次把 nTimes 设为 1 的数字 */

template<typename Tp>
Tp moreThanHalf(Tp const* inArr, int const len)
{
	if (len < 1) return inArr[0]; // 0 的话，崩溃就崩溃吧，非传空数组怪谁
	Tp cand = inArr[0];
	int nTime = 1;
	for (int k = 1; k < len; ++k)
	{
		if (nTime == 0)
		{
			cand = inArr[k];
			nTime = 1;
		}
		else if (cand == inArr[k])
			nTime++;
		else
			nTime--;
	}
	return cand;
}

int main()
{
	int const n = 5;
	int const arr[n] = { 0, 1, 2, 1, 1 };
	printf("\n%d", moreThanHalf(arr, n));
	printf("\n");
	return 0;
}
