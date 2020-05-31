#include "leetcode.hpp"

/* 306. 累加数

累加数是一个字符串，组成它的数字可以形成累加序列。

一个有效的累加序列必须至少包含 3 个数。
除了最开始的两个数以外，字符串中的其他数都等于它之前两个数相加的和。

给定一个只包含数字 '0'-'9' 的字符串，编写一个算法来判断给定输入是否是累加数。

说明: 累加序列里的数不会以 0 开头，所以不会出现 1, 2, 03 或者 1, 02, 3 的情况。

示例 1:
输入: "112358"
输出: true
解释: 累加序列为: 1, 1, 2, 3, 5, 8 。1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8

示例 2:
输入: "199100199"
输出: true
解释: 累加序列为: 1, 99, 100, 199。1 + 99 = 100, 99 + 100 = 199

进阶:
你如何处理一个溢出的过大的整数输入?
*/

// https://leetcode.com/problems/additive-number/discuss/75576/0ms-concise-C%2B%2B-solution-(perfectly-handles-the-follow-up-and-leading-0s)
// 抄的
class Solution
{
public:
	// 抄的
	string add(string const& x, string const& y)
	{
		string z;
		ptrdiff_t i = x.size() - 1, k = y.size() - 1;
		int carry = 0;
		while (i >= 0 || k >= 0)
		{
			int sum = carry
				+ (i >= 0 ? (x[i--] - '0') : 0)
				+ (k >= 0 ? (y[k--] - '0') : 0);
			z.push_back(sum % 10 + '0');
			carry = sum / 10;
		}
		if (carry)
			z.push_back(carry + '0');
		std::reverse(z.begin(), z.end());
		return z;
	}


	bool check(string const& n1, string const& n2, string const& rest)
	{
		if ((n1.size() > 1 && n1[0] == '0')
			|| (n2.size() > 1 && n2[0] == '0'))
			return false;

		string sum = add(n1, n2);
		if (sum == rest)
			return true;

		if (rest.size() <= sum.size()
			|| sum != rest.substr(0, sum.size()))
			return false;

		return check(n2, sum, rest.substr(sum.size()));
	}

	bool isAdditiveNumber(string num)
	{
		size_t const len = num.size();
		for (size_t i = 1; i <= len / 2; ++i)
			for (size_t k = 1; k <= (len - i) / 2; ++k)
			{
				if (check(num.substr(0, i), num.substr(i, k), num.substr(i + k)))
					return true;
			}
		return false;
	}
};


int main()
{}
