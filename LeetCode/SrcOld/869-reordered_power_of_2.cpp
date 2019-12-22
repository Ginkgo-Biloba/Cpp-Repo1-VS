#include "leetcode.hpp"

/* 869. 重新排序得到 2 的幂

给定正整数 N，我们按任何顺序（包括原始顺序）将数字重新排序，注意其前导数字不能为零。

如果我们可以通过上述方式得到 2 的幂，返回 true；否则，返回 false。

示例 1：
输入：1
输出：true

示例 2：
输入：10
输出：false

示例 3：
输入：16
输出：true

示例 4：
输入：24
输出：false

示例 5：
输入：46
输出：true

提示：
	1 <= N <= 10^9
*/

bool reorderedPowerOf2(int N)
{
	char buf[64];
	vector<string> s;
	s.reserve(64);

	for (int i = 0; i < 61; ++i)
	{
		long long q = 1LL << i;
		sprintf(buf, "%lld", q);
		s.emplace_back(buf);
		sort(s.back().begin(), s.back().end());
	}

	sprintf(buf, "%d", N);
	string n(buf);
	sort(n.begin(), n.end());
	return std::find(s.begin(), s.end(), n) != s.end();
}

int main()
{
	OutBool(reorderedPowerOf2(1));
	OutBool(reorderedPowerOf2(10));
	OutBool(reorderedPowerOf2(16));
	OutBool(reorderedPowerOf2(24));
	OutBool(reorderedPowerOf2(46));
}
