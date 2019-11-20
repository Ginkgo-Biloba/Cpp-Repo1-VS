#include "leetcode.hpp"

/* 753. 破解保险箱

有一个需要密码才能打开的保险箱。
密码是 n 位数, 密码的每一位是 k 位序列 0, 1, ..., k-1 中的一个 。
你可以随意输入密码，保险箱会自动记住最后 n 位输入，如果匹配，则能够打开保险箱。
举个例子，假设密码是 "345"，你可以输入 "012345" 来打开它，只是你输入了 6 个字符.
请返回一个能打开保险箱的最短字符串。

示例1:
输入: n = 1, k = 2
输出: "01"
说明: "10"也可以打开保险箱。

示例2:
输入: n = 2, k = 2
输出: "00110"
说明: "01100", "10011", "11001" 也能打开保险箱。

提示：
	n 的范围是 [1, 4]。
	k 的范围是 [1, 10]。
	k^n 最大可能为 4096。
*/

// https://leetcode.com/problems/cracking-the-safe/discuss/110260/De-Bruijn-sequence-C%2B%2B
// 抄的
class Solution
{
	vector<char> visit;
	string seq;
	int n, k, kn1;

	int at(int y, int x)
	{
		return y * k + x;
	}

	void dfs(int u)
	{
		for (int i = 0; i < k; ++i)
			if (!visit[at(u, i)])
			{
				visit[at(u, i)] = 1;
				dfs((u * k + i) % kn1);
				seq.push_back(static_cast<char>('0' + i));
			}
	}

public:
	string crackSafe(int _n, int _k)
	{
		n = _n;
		k = _k;
		if (k == 1)
			return string(n, '0');
		kn1 = 1;
		for (int i = 1; i < n; ++i)
			kn1 *= k;
		visit.resize(kn1 * k);
		memset(visit.data(), 0, kn1 * k * sizeof(char));
		dfs(0);
		return seq + seq.substr(0, n - 1);
	}
};


int main()
{
	Solution s;
	OutExpr(s.crackSafe(1, 2).c_str(), "%s");
	OutExpr(s.crackSafe(2, 2).c_str(), "%s");
}
