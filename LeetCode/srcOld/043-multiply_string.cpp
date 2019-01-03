#include <string>
#include <iostream>
#include <ctime>

/* 字符串表示的大自然数相乘 */
/* 将短的放在前面，长的放在后面会更好 */
/* 空串视为 0 */
std::string multipy_string(std::string const& num1, std::string const& num2)
{
	// if (num1.length() > num2.length()) return multipy_string(num2, num1);
	size_t const stop = (size_t)(-1);
	size_t n1 = num1.length(), n2 = num2.length();
	size_t len1, len2, len;
	// 去除尾随 0
	for (len1 = n1 - 1u; len1 != stop && num1[len1] == '0'; len1--);
	for (len2 = n2 - 1u; len2 != stop && num2[len2] == '0'; len2--);
	// 0 直接扔了
	if (len1 == stop || len2 == stop) return std::string("0");
	// 1 返回另外一个数加上尾随 0 的个数，事实证明还不如不判断直接乘……
	size_t tail1 = n1 - len1 - 1u, tail2 = n2 - len2 - 1u;
	if (len1 == 0u && num1[0] == '1') return num2 + std::string(tail1, '0');
	if (len2 == 0u && num2[0] == '1') return num1 + std::string(tail2, '0');

	len = len1 + len2 + 2u;
	std::string tmp, ans(len, '\0'); tmp.reserve(n1 + n2);
	size_t i, k, ik;
	char const R = 10;
	char sum, carry, c;
	// 转为数字，因为在内层循环
	for (i = 0u; i <= len1; i++) tmp.push_back(num1[i] - '0');

	/* 乘法，string 从左向右生长 */
	for (k = len2; k != stop; k--)
	{
		c = num2[k] - '0';
		if (c == 0) continue; // 0 就不用算了
		carry = 0;
		for (i = len1; i != stop; i--)
		{
			ik = i + k + 1u;
			sum = ans[ik] + tmp[i] * c;
			sum += carry;
			ans[ik] = (sum % R);
			carry = sum / R;
		}
		ans[k] += carry;
	}

	/* 去除前导 0，并转为字符串 */
	tmp.clear();
	for (i = 0u; i < len && ans[i] == '\0'; i++);
	for (; i < len; i++)
		tmp.push_back(ans[i] + '0');
	tmp.resize(tmp.size() + tail1 + tail2, '0');
	return tmp;
}

int main()
{
	typedef unsigned int uint;
	std::string num1("99992835923793251390");
	std::string num2("9343299879777786757734237767");
	// 934263051865417442583022350511797181300263246130
	std::string ans = multipy_string(num1, num2);
	std::cout << num1 << " × " << num2 << " = " << ans << "\n";

	uint i, n; std::cin >> n;
	ans = std::string("1");
	clock_t st = clock();
	for (i = 2u; i <= n; i++)
		ans = multipy_string(std::to_string(i), ans);
	clock_t ed = clock();
	std::cout << n << "! =\n\t" << ans << "\n";
	std::cout << "Elapse " << (ed - st) << " clocks\n";
	return 0;
}

