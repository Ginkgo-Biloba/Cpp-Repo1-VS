#include "leetcode.hpp"

/* 1405. 最长快乐字符串

如果字符串中不含有任何 'aaa'，'bbb' 或 'ccc' 这样的字符串作为子串，那么该字符串就是一个「快乐字符串」。

给你三个整数 a，b ，c，请你返回 任意一个 满足下列全部条件的字符串 s：
	s 是一个尽可能长的快乐字符串。
	s 中 最多 有a 个字母 'a'、b 个字母 'b'、c 个字母 'c' 。
	s 中只含有 'a'、'b' 、'c' 三种字母。

如果不存在这样的字符串 s ，请返回一个空字符串 ""。

示例 1：
输入：a = 1, b = 1, c = 7
输出："ccaccbcc"
解释："ccbccacc" 也是一种正确答案。

示例 2：
输入：a = 2, b = 2, c = 1
输出："aabbc"

示例 3：
输入：a = 7, b = 1, c = 0
输出："aabaa"
解释：这是该测试用例的唯一正确答案。

提示：
	0 <= a, b, c <= 100
	a + b + c > 0
*/

typedef pair<int, char> pic;

void large_op(pic& a, pic& b)
{
	// 如果相等，也交换
	pic t = a;
	a = (b.first < a.first) ? a : b;
	b = (b.first < t.first) ? b : t;
}

void large_op(pic* T)
{
	large_op(T[0], T[1]);
	large_op(T[0], T[2]);
	large_op(T[1], T[2]);
}

string longestDiverseString(int a, int b, int c)
{
	string S;
	pic T[3] = { { a, 'a' }, { b, 'b' }, { c, 'c' } };
	large_op(T);
	for (int i = 0; T[0].first > 0; ++i)
	{
		char ch = T[0].second;
		if ((i < 2)
			|| (S[i - 1] != ch)
			|| (S[i - 2] != ch))
		{
			S.push_back(ch);
			T[0].first -= 1;
		}
		else if (T[1].first > 0)
		{
			S.push_back(T[1].second);
			T[1].first -= 1;
		}
		else
			break;
		large_op(T);
	}
	return S;
}

int main()
{
	OutString(longestDiverseString(1, 1, 7));
	OutString(longestDiverseString(2, 2, 1));
	OutString(longestDiverseString(7, 1, 0));
}
