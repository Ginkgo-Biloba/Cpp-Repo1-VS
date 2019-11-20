#include "leetcode.hpp"

/* 752. 打开转盘锁

你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' 。
每个拨轮可以自由旋转：例如把 '9' 变为  '0'，'0' 变为 '9'。
每次旋转都只能旋转一个拨轮的一位数字。

锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。

列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。

字符串 target 代表可以解锁的数字，你需要给出最小的旋转次数，如果无论如何不能解锁，返回 -1。

示例 1:
输入：deadends = ["0201","0101","0102","1212","2002"], target = "0202"
输出：6
解释：
可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。
注意 "0000" -> "0001" -> "0002" -> "0102" -> "0202" 这样的序列是不能解锁的，
因为当拨动到 "0102" 时这个锁就会被锁定。

示例 2:
输入: deadends = ["8888"], target = "0009"
输出：1
解释：
把最后一位反向旋转一次即可 "0000" -> "0009"。

示例 3:
输入: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
输出：-1
解释：
无法旋转到目标数字且不被锁定。

示例 4:
输入: deadends = ["0000"], target = "8888"
输出：-1

提示：
	死亡列表 deadends 的长度范围为 [1, 500]。
	目标数字 target 不会在 deadends 之中。
	每个 deadends 和 target 中的字符串的数字会在 10,000 个可能的情况 '0000' 到 '9999' 中产生。
*/

class Solution
{
	static size_t const LEN = 0x9fff;
	int step[LEN], q[LEN];
	int dst, qsz;

	inline int merge(string const& str)
	{
		int i
			= ((str[0] - '0') << 0)
			| ((str[1] - '0') << 4)
			| ((str[2] - '0') << 8)
			| ((str[3] - '0') << 12);
		return i;
	}
	inline int merge(int const* ptr)
	{
		int i
			= (ptr[0] << 0)
			| (ptr[1] << 4)
			| (ptr[2] << 8)
			| (ptr[3] << 12);
		return i;
	}
	inline void split(int i, int* ptr)
	{
		ptr[0] = 0xf & (i >> 0);
		ptr[1] = 0xf & (i >> 4);
		ptr[2] = 0xf & (i >> 8);
		ptr[3] = 0xf & (i >> 12);
	}

public:
	int openLock(vector<string>& deadends, string target)
	{
		int num[4], idx = 0, old;
		memset(step, 0x7f, sizeof(step));
		for (string const& dead : deadends)
		{
			dst = merge(dead);
			step[dst] = -1;
		}
		if (step[0] == -1)
			return -1;
		dst = merge(target);
		step[0] = 0;
		q[0] = 0;
		qsz = 1;

		for (; idx < qsz; ++idx)
		{
			int cur = q[idx];
			int s1 = step[cur] + 1;
			split(cur, num);
			for (int b = 0; b < 4; ++b)
			{
				old = num[b];
				num[b] = (old + 1) % 10;
				cur = merge(num);
				if (step[cur] > s1)
				{
					if (cur == dst)
						return s1;
					step[cur] = s1;
					q[qsz] = cur;
					++qsz;
				}
				num[b] = (old + 9) % 10;
				cur = merge(num);
				if (step[cur] > s1)
				{
					if (cur == dst)
						return s1;
					step[cur] = s1;
					q[qsz] = cur;
					++qsz;
				}
				num[b] = old;
			}
		}

		return -1;
	}
};


int main()
{
	vector<string>
		d0 = { "0201", "0101", "0102", "1212", "2002" },
		d1 = { "8888" },
		d2 = { "8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888" },
		d3 = { "0000" };
	Solution s;
	OutExpr(s.openLock(d0, "0202"), "%d");
	OutExpr(s.openLock(d1, "0009"), "%d");
	OutExpr(s.openLock(d2, "8888"), "%d");
	OutExpr(s.openLock(d3, "8888"), "%d");
}
