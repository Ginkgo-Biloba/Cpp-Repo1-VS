#include "leetcode.hpp"

/* 1622. 奇妙序列

请你实现三个 API append，addAll 和 multAll 来实现奇妙序列。

请实现 Fancy 类 ：
	Fancy() 初始化一个空序列对象。
	void append(val) 将整数 val 添加在序列末尾。
	void addAll(inc) 将所有序列中的现有数值都增加 inc 。
	void multAll(m) 将序列中的所有现有数值都乘以整数 m 。
	int getIndex(idx) 得到下标为 idx 处的数值（下标从 0 开始），并将结果对 109 + 7 取余。如果下标大于等于序列的长度，请返回 -1 。

示例：
输入：
["Fancy", "append", "addAll", "append", "multAll", "getIndex", "addAll", "append", "multAll", "getIndex", "getIndex", "getIndex"]
[[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]
输出：
[null, null, null, null, null, 10, null, null, null, 26, 34, 20]

解释：
Fancy fancy = new Fancy();
fancy.append(2);   // 奇妙序列：[2]
fancy.addAll(3);   // 奇妙序列：[2+3] -> [5]
fancy.append(7);   // 奇妙序列：[5, 7]
fancy.multAll(2);  // 奇妙序列：[5*2, 7*2] -> [10, 14]
fancy.getIndex(0); // 返回 10
fancy.addAll(3);   // 奇妙序列：[10+3, 14+3] -> [13, 17]
fancy.append(10);  // 奇妙序列：[13, 17, 10]
fancy.multAll(2);  // 奇妙序列：[13*2, 17*2, 10*2] -> [26, 34, 20]
fancy.getIndex(0); // 返回 26
fancy.getIndex(1); // 返回 34
fancy.getIndex(2); // 返回 20

提示：
	1 <= val, inc, m <= 100
	0 <= idx <= 10^5
	总共最多会有 10^5 次对 append，addAll，multAll 和 getIndex 的调用。
*/

// https://leetcode.com/problems/fancy-sequence/discuss/898753/Python-Time-O(1)-for-each
// 抄的
class Fancy
{
	enum { mod = (int)(1e9 + 7) };
	vector<int> A, add, mul;

	int64_t ipow(int64_t a, int64_t q)
	{
		int64_t b = 1;
		for (; q; q >>= 1)
		{
			if (q & 1)
				b = (b * a) % mod;
			a = (a * a) % mod;
		}
		return b;
	}

public:
	Fancy()
	{
		add.push_back(0);
		mul.push_back(1);
	}

	void append(int val)
	{
		A.push_back(val);
		add.push_back(add.back());
		mul.push_back(mul.back());
	}

	void addAll(int inc)
	{
		add.back() = (add.back() + inc) % mod;
	}

	void multAll(int m)
	{
		add.back() = (int)((int64_t)(add.back()) * m % mod);
		mul.back() = (int)((int64_t)(mul.back()) * m % mod);
	}

	int getIndex(int i)
	{
		if ((size_t)(i) >= A.size())
			return -1;
		int64_t m = (int64_t)(mul.back()) * ipow(mul[i], mod - 2) % mod;
		int64_t p = (int64_t)(add.back()) + mod - (add[i] * m) % mod;
		return (int)((A[i] * m + p) % mod);
	}
};


int main()
{}
