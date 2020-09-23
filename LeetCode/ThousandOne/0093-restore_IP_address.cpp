#include "leetcode.hpp"

/* 93. 复原IP地址

给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

有效的 IP 地址正好由四个整数（每个整数位于 0 到 255 之间组成），整数之间用 '.' 分隔。

示例:
输入: "25525511135"
输出: ["255.255.11.135", "255.255.111.35"]
*/

vector<string> restoreIpAddresses(string s)
{
	int len = static_cast<int>(s.length());
	int a = 0, b, c, d;
	char buf[32] = { 0 };
	vector<string> ans;
	// 第 2 段开始
	for (int h = 1; h < len; ++h)
	{
		a = a * 10 + s[h - 1] - '0';
		if (a > 255)
			break;
		b = 0;
		// 第 3 段开始
		for (int i = h + 1; i < len; ++i)
		{
			b = b * 10 + s[i - 1] - '0';
			if (b > 255)
				break;
			c = 0;
			// 第 4 段开始
			for (int k = i + 1; k < len; ++k)
			{
				c = c * 10 + s[k - 1] - '0';
				if (c > 255)
					break;
				if (k + 3 < len)
					continue;
				d = 0;
				for (int n = k; n < len; ++n)
					d = d * 10 + s[n] - '0';
				if (d > 255)
					continue;
				if (snprintf(buf, sizeof(buf),
					"%d.%d.%d.%d", a, b, c, d)
					== len + 3)
					ans.push_back(string(buf));
			}
		}
	}
	return ans;
}


int main()
{
	output(restoreIpAddresses("172162541"), ", ", "Restore IP Addresses");
	output(restoreIpAddresses("25525511135"), ", ", "Restore IP Addresses");
}
