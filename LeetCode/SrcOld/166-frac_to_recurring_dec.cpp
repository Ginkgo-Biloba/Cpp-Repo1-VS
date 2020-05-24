#include "leetcode.hpp"

/* 166. 分数到小数

给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以字符串形式返回小数。

如果小数部分为循环小数，则将循环的部分括在括号内。

示例 1:
输入: numerator = 1, denominator = 2
输出: "0.5"

示例 2:
输入: numerator = 2, denominator = 1
输出: "2"

示例 3:
输入: numerator = 2, denominator = 3
输出: "0.(6)"
*/

// 抄的
string fractionToDecimal(int num, int den)
{
	bool neg = (num > 0 && den < 0) || (num < 0 && den > 0);
	int64_t A = std::abs(static_cast<int64_t>(num));
	int64_t B = std::abs(static_cast<int64_t>(den));
	// 计算 A ÷ B = C...D
	// C++ 商向 0 取整，结果是余数和被除数符号一致
	int64_t C = A / B;
	int64_t D = A - C * B;

	char buf[16];
	if (neg)
		sprintf(buf, "-%llu", C);
	else
		sprintf(buf, "%llu", C);
	string s(buf);
	if (D == 0)
		return s;

	s.push_back('.');
	map<int64_t, int> residual;
	int bitbeg, bitcur = 0;
	for (; D != 0; ++bitcur)
	{
		D *= 10;
		int64_t q = D / B;
		s.push_back(static_cast<char>(q + '0'));
		map<int64_t, int>::iterator iter = residual.find(D);
		if (iter == residual.end())
			residual.emplace(D, bitcur);
		else
		{
			bitbeg = iter->second;
			break;
		}
		D -= q * B;
	}

	if (D != 0) // 循环小数
	{
		// 直接覆盖掉多 push_back 进去那个商
		size_t len = s.size() - 1u;
		for (int repbit = bitcur - bitbeg; repbit--; --len)
			s[len] = s[len - 1u];
		s[len] = '(';
		s.push_back(')');
	}

	return s;
}


int main()
{
	OutString(fractionToDecimal(1, 2));
	OutString(fractionToDecimal(2, 1));
	OutString(fractionToDecimal(2, 3));
	OutString(fractionToDecimal(2, 7));
}
