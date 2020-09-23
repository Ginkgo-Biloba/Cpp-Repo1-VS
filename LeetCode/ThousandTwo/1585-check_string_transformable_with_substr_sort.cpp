#include "leetcode.hpp"

/* 1585. 检查字符串是否可以通过排序子字符串得到另一个字符串

给你两个字符串 s 和 t ，请你通过若干次以下操作将字符串 s 转化成字符串 t ：
	选择 s 中一个 非空 子字符串并将它包含的字符就地 升序 排序。

比方说，对下划线所示的子字符串进行操作可以由 "14234" 得到 "12344" 。

如果可以将字符串 s 变成 t ，返回 true 。
否则，返回 false 。

一个 子字符串 定义为一个字符串中连续的若干字符。

示例 1：
输入：s = "84532", t = "34852"
输出：true
解释：你可以按以下操作将 s 转变为 t ：
"84532" （从下标 2 到下标 3）-> "84352"
"84352" （从下标 0 到下标 2） -> "34852"

示例 2：
输入：s = "34521", t = "23415"
输出：true
解释：你可以按以下操作将 s 转变为 t ：
"34521" -> "23451"
"23451" -> "23415"

示例 3：
输入：s = "12345", t = "12435"
输出：false

示例 4：
输入：s = "1", t = "2"
输出：false

提示：
	s.length == t.length
	1 <= s.length <= 105
	s 和 t 都只包含数字字符，即 '0' 到 '9' 。
*/


// 赛后抄的第一名的
// 依次递减对于从 9-0 的每个数字，s 的位置不能在 t 后面
bool isTransformable(string s, string t)
{
	string a, b;
	vector<int> apos, bpos;
	for (int c = '9'; c >= '0'; --c)
	{
		a.clear();
		b.clear();
		apos.clear();
		bpos.clear();
		int len = static_cast<int>(s.size());
		for (int i = 0; i < len; ++i)
		{
			if (s[i] == c)
				apos.push_back(i);
			else if (s[i] < c)
				a.push_back(s[i]);
			if (t[i] == c)
				bpos.push_back(i);
			else if (t[i] < c)
				b.push_back(t[i]);
		}
		if (apos.size() != bpos.size())
			return false;
		int k = static_cast<int>(apos.size());
		for (--k; k >= 0; --k)
		{
			if (apos[k] > bpos[k])
				return false;
		}
		a.swap(s);
		b.swap(t);
	}
	return true;
}

// https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/discuss/843917/C%2B%2BJavaPython-O(n)
// 抄的
// 这里是检查 s 中当前位置的前面，不能有比 t 中当前字符小的字符
// 毕竟题目说只能正序排序，不能逆序
bool isTransformable2(string s, string t)
{
	vector<int> idx[10];
	size_t pos[10] = { 0 };
	int len = static_cast<int>(s.size());
	for (int i = 0; i < len; ++i)
		idx[s[i] - '0'].push_back(i);
	for (int i = 0; i < len; ++i)
	{
		int d = t[i] - '0';
		if (pos[d] >= idx[d].size())
			return false;
		for (int k = 0; k < d; ++k)
		{
			if (pos[k] < idx[k].size()
				&& idx[k][pos[k]] < idx[d][pos[d]])
				return false;
		}
		++(pos[d]);
	}
	return true;
}


int main()
{
	OutBool(isTransformable("84532", "34852"));
	OutBool(isTransformable("34521", "23415"));
	OutBool(isTransformable("12345", "12435"));
	OutBool(isTransformable("1", "2"));
	OutBool(isTransformable("8123", "2138"));
}
