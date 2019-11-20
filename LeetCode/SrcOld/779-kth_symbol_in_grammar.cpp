#include "leetcode.hpp"

/* 779. 第K个语法符号

在第一行我们写上一个 0。接下来的每一行，将前一行中的0替换为01，1替换为10。

给定行数 N 和序数 K，返回第 N 行中第 K个字符。（K从1开始）


例子:

输入: N = 1, K = 1
输出: 0

输入: N = 2, K = 1
输出: 0

输入: N = 2, K = 2
输出: 1

输入: N = 4, K = 5
输出: 1

解释:
第一行: 0
第二行: 01
第三行: 0110
第四行: 01101001

注意：
		N 的范围 [1, 30].
		K 的范围 [1, 2^(N-1)].
*/

// https://leetcode-cn.com/problems/k-th-symbol-in-grammar/solution/di-kge-yu-fa-fu-hao-by-ikaruga-2/

int kth(int K)
{
	return (K < 2) ? K : ((K & 1) ^ kth(K / 2));
}
// 有坑，K 和 N 都是从 1 开始
int kthGrammar(int, int K)
{
	return kth(K - 1);
}

int main()
{
	OutExpr(kthGrammar(2, 1), "%d");
	OutExpr(kthGrammar(3, 2), "%d");
	OutExpr(kthGrammar(4, 5), "%d");
}
