#include "leetcode.hpp"

/* 17. 电话号码的字母组合

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
http://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Telephone-keypad2.svg/200px-Telephone-keypad2.svg.png
https://assets.leetcode-cn.com/aliyun-lc-upload/original_images/17_telephone_keypad.png

示例:
输入："23"
输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

说明:
尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。
*/

string const cand[10] = {
	"",
	"",
	"abc",
	"def",
	"ghi",
	"jkl",
	"mno",
	"pqrs",
	"tuv",
	"wxyz",
};

vector<string> letterCombinations(string digits)
{
	int len = static_cast<int>(digits.length());
	int sum = 1, pre = 1, cur;
	vector<string> R;
	if (len < 1)
		return R;
	for (int i = 0; i < len; ++i)
		sum *= static_cast<int>(cand[digits[i] - '0'].size());
	R.resize(sum, string(len, '0'));
	for (int i = len - 1; i >= 0; --i)
	{
		int dig = digits[i] - '0';
		char const* ptr = cand[dig].data();
		cur = static_cast<int>(cand[dig].size());
		for (int h = 0; h < sum;)
			for (int c = 0; c < cur; ++c)
				for (int p = 0; p < pre; ++p)
				{
					R[h][i] = ptr[c];
					++h;
				}
		pre *= cur;
	}
	return R;
}

int main()
{
	output(letterCombinations("23"), ", ", "Phone");
}
