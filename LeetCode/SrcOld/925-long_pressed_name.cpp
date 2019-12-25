#include "leetcode.hpp"

/* 925. 长按键入

你的朋友正在使用键盘输入他的名字 name。
偶尔，在键入字符 c 时，按键可能会被长按，而字符可能被输入 1 次或多次。

你将会检查键盘输入的字符 typed。
如果它对应的可能是你的朋友的名字（其中一些字符可能被长按），那么就返回 True。

示例 1：
输入：name = "alex", typed = "aaleex"
输出：true
解释：'alex' 中的 'a' 和 'e' 被长按。

示例 2：
输入：name = "saeed", typed = "ssaaedd"
输出：false
解释：'e' 一定需要被键入两次，但在 typed 的输出中不是这样。

示例 3：
输入：name = "leelee", typed = "lleeelee"
输出：true

示例 4：
输入：name = "laiden", typed = "laiden"
输出：true
解释：长按名字中的字符并不是必要的。

提示：
	name.length <= 1000
	typed.length <= 1000
	name 和 typed 的字符都是小写字母。
*/

bool isLongPressedName(string name, string typed)
{
	size_t N = name.size(), T = typed.size();
	size_t n = 0, t = 0;
	char prev = 0;
	while (n < N && t < T)
	{
		if (name[n] == typed[t])
		{
			prev = name[n];
			++n;
			++t;
		}
		else if (prev == typed[t])
			++t;
		else
			return false;
	}
	while (t < T && prev == typed[t])
		++t;
	return n == N && t == T;
}

int main()
{
	OutBool(isLongPressedName("alex", "aaleex"));
	OutBool(isLongPressedName("saeed", "ssaaedd"));
	OutBool(isLongPressedName("leelee", "lleeelee"));
	OutBool(isLongPressedName("laiden", "laiden"));
}
