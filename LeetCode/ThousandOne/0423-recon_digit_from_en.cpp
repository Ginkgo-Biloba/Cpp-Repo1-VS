#include "leetcode.hpp"

/* 423. 从英文中重建数字
给定一个非空字符串，其中包含字母顺序打乱的英文单词表示的数字0-9。按升序输出原始的数字。
注意:
		输入只包含小写英文字母。
		输入保证合法并可以转换为原始的数字，这意味着像 "abc" 或 "zerone" 的输入是不允许的。
		输入字符串的长度小于 50,000。

示例 1:
输入: "owoztneoer"
输出: "012" (zeroonetwo)

示例 2:
输入: "fviefuro"
输出: "45" (fourfive)
*/

// https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/discuss/91049/Java-O(n)-solution-using-bit-manipulation-and-HashMap
// 抄的
string originalDigits(string const& s)
{
	int hist[127];
	memset(hist, 0, sizeof(hist));
	for (char c : s)
		++(hist[c]);

	hist[0] = hist['z']; // zero
	hist[2] = hist['w']; // two
	hist[4] = hist['u']; // four
	hist[6] = hist['x']; // six
	hist[8] = hist['g']; // eight
	hist[1] = hist['o'] - hist[0] - hist[2] - hist[4]; // one
	hist[3] = hist['h'] - hist[8]; // three
	hist[7] = hist['s'] - hist[6]; // seven
	hist[5] = hist['v'] - hist[7]; // five
	hist[9] = hist['i'] - hist[5] - hist[6] - hist[8]; // nine

	string ans;
	for (int i = 0; i < 10; ++i)
		if (hist[i] > 0)
		{
			char c = '0' + i;
			ans.reserve(ans.size() + hist[i]);
			for (int h = 0; h < hist[i]; ++h)
				ans.push_back(c);
		}
	return ans;
}


int main()
{
	OutExpr(originalDigits("zero").c_str(), "%s");
}
