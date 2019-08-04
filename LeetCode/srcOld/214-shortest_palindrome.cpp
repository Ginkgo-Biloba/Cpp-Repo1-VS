#include "leetcode.hpp"


class Solution
{
	/* 都是抄的 */
protected:
	string cvtKMP(string const& str)
	{
		string rev = str;
		std::reverse(rev.begin(), rev.end());
		string longstr = str + "#" + rev;

		size_t len = longstr.size();
		// 这个表，第 i 位存的是普通 KMP 的第 i + 1 位
		vector<size_t> kmp(longstr.size(), 0);
		for (size_t i = 1; i < len; ++i)
		{
			size_t k = kmp[i - 1u];
			while (k > 0 && longstr[i] != longstr[k])
				k = kmp[k - 1u];
			kmp[i] = k + (longstr[k] == longstr[i] ? 1u : 0);
		}

		longstr = rev.substr(0, str.size() - kmp.back()) + str;
		return longstr;
	}


	string cvtRabinKarp(string const& str)
	{
		static unsigned const sBase = 127u;
		static unsigned const sMod = 65521u; // 平方不大于 UINT_MAX 的最大质数;
		unsigned len = static_cast<unsigned>(str.size());
		if (len < 2u) return str;
		string rev = str;
		std::reverse(rev.begin(), rev.end());

		vector<unsigned> hRevS(len + 1u), hPower(len + 1u);
		for (unsigned i = len - 1u; i != (unsigned)(-1); --i)
			hRevS[i] = (hRevS[i + 1] * sBase + str[i]) % sMod;
		hPower[0] = 1u;
		for (unsigned i = 1; i <= len; ++i)
			hPower[i] = (hPower[i - 1u] * sBase) % sMod;

		unsigned maxlen = 0, hStr = 0;
		for (unsigned i = 1; i <= len; ++i)
		{
			hStr = (hStr * sBase + str[i - 1u]) % sMod;
			unsigned hRev = (hRevS[0] + sMod - hRevS[i] * hPower[i] % sMod) % sMod;
			if ((hStr == hRev) &&
				!memcmp(str.data(), rev.data() + len - i, i * sizeof(char)))
				maxlen = i;
		}

		string ans = rev.substr(0, len - maxlen) + str;
		return ans;
	}


public:
	string shortestPalindrome(string const& str)
	{
#if 0
			return cvtKMP(str);
#else
			return cvtRabinKarp(str);
#endif
	}
};


int main()
{
	string s1 = "aacecaaa", s2 = "abcd";
	string s3 = "jthytanacixafroxbafwrxaowkizowlozikzojwccnsdgfsmafgspuvxh";
	Solution sln;
	s1 = sln.shortestPalindrome(s1); 
	s2 = sln.shortestPalindrome(s2); 
	s3 = sln.shortestPalindrome(s3); 
	// aaacecaaa
	// dcbabcd
	// hxvupsgfamsfgdsnccwjozkizolwozikwoaxrwfabxorfaxicanatyhtjthytanacixafroxbafwrxaowkizowlozikzojwccnsdgfsmafgspuvxh
	printf("Shortest Palindrome: \n%s\n%s\n%s\n",
		s1.c_str(), s2.c_str(), s3.c_str());
}
