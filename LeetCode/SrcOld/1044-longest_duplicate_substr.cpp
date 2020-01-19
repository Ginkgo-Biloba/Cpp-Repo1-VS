#include "leetcode.hpp"

/* 1044. 最长重复子串

给出一个字符串 S，考虑其所有重复子串（S 的连续子串，出现两次或多次，可能会有重叠）。

返回任何具有最长可能长度的重复子串。
如果 S 不含重复子串，那么答案为 ""。

示例 1：
输入："banana"
输出："ana"

示例 2：
输入："abcd"
输出：""

提示：
	2 <= S.length <= 10^5
	S 由小写英文字母组成。
*/


// 抄的
class Solution
{
	enum { Mod = 159072857 }; // *27+26 < UINT_MAX

	int len;
	string str, ans;
	vector<unsigned> mul;
	vector<pair<unsigned, int>> rks; // Rabin Karp

	bool check(int M)
	{
		if (M == 0)
			return false;
		rks.clear();
		unsigned cur = 0, sub;
		int i = 0;
		char const* S = str.data();
		for (; i < M - 1; ++i)
			cur = (cur * 26 + (str[i] - 'a')) % Mod;
		for (; i < len; ++i)
		{
			cur = (cur * 26 + (str[i] - 'a')) % Mod;
			rks.emplace_back(cur, i - M + 1);
			sub = ((str[i - M + 1] - 'a') * mul[M - 1]) % Mod;
			cur = (cur - sub + Mod) % Mod;
		}
		assert(rks.size() == static_cast<size_t>(len - M + 1));
		sort(rks.begin(), rks.end());
		for (i = len - M; i > 0; --i)
		{
			if (rks[i].first == rks[i - 1].first
				&& !memcmp(S + rks[i].second, S + rks[i - 1].second,
					M * sizeof(char)))
			{
				ans = str.substr(rks[i].second, M);
				return true;
			}
		}
		return false;
	}

public:
	Solution()
	{
		mul.reserve(100000);
		unsigned cur = 1;
		mul.push_back(1);
		for (int i = 1; i <= 100000; ++i)
		{
			cur = cur * 26 % Mod;
			mul.push_back(cur);
		}
	}

	string longestDupSubstring(string S)
	{
		ans.clear();
		str.swap(S);
		len = static_cast<int>(str.size());

		int L = 0, M, R = len - 1;
		while (L < R)
		{
			// 往小搜这里要加 1
			// 考虑死循环 (L=3, R=4, M=3, check=true) 
			M = (L + R + 1) / 2;
			if (check(M))
				L = M;
			else
				R = M - 1;
		}
		return ans;
	}
};


int main()
{
	Solution s;
	OutString(s.longestDupSubstring("moplvidmaagmsiyyrkchbyhivlqwqsjcgtumqscmxrxrvwsnjjvygrelcbjgbpounhuyealllginkitfaiviraqcycjmskrozcdqylbuejrgfnquercvghppljmojfvylcxakyjxnampmakyjbqgwbyokaybcuklkaqzawageypfqhhasetugatdaxpvtevrigynxbqodiyioapgxqkndujeranxgebnpgsukybyowbxhgpkwjfdywfkpufcxzzqiuglkakibbkobonunnzwbjktykebfcbobxdflnyzngheatpcvnhdwkkhnlwnjdnrmjaevqopvinnzgacjkbhvsdsvuuwwhwesgtdzuctshytyfugdqswvxisyxcxoihfgzxnidnfadphwumtgdfmhjkaryjxvfquucltmuoosamjwqqzeleaiplwcbbxjxxvgsnonoivbnmiwbnijkzgoenohqncjqnckxbhpvreasdyvffrolobxzrmrbvwkpdbfvbwwyibydhndmpvqyfmqjwosclwxhgxmwjiksjvsnwupraojuatksjfqkvvfroqxsraskbdbgtppjrnzpfzabmcczlwynwomebvrihxugvjmtrkzdwuafozjcfqacenabmmxzcueyqwvbtslhjeiopgbrbvfbnpmvlnyexopoahgmwplwxnxqzhucdieyvbgtkfmdeocamzenecqlbhqmdfrvpsqyxvkkyfrbyolzvcpcbkdprttijkzcrgciidavsmrczbollxbkytqjwbiupvsorvkorfriajdtsowenhpmdtvamkoqacwwlkqfdzorjtepwlemunyrghwlvjgaxbzawmikfhtaniwviqiaeinbsqidetfsdbgsydkxgwoqyztaqmyeefaihmgrbxzyheoegawthcsyyrpyvnhysynoaikwtvmwathsomddhltxpeuxettpbeftmmyrqclnzwljlpxazrzzdosemwmthcvgwtxtinffopqxbufjwsvhqamxpydcnpekqhsovvqugqhbgweaiheeicmkdtxltkalexbeftuxvwnxmqqjeyourvbdfikqnzdipmmmiltjapovlhkpunxljeutwhenrxyfeufmzipqvergdkwptkilwzdxlydxbjoxjzxwcfmznfqgoaemrrxuwpfkftwejubxkgjlizljoynvidqwxnvhngqakmmehtvykbjwrrrjvwnrteeoxmtygiiygynedvfzwkvmffghuduspyyrnftyvsvjstfohwwyxhmlfmwguxxzgwdzwlnnltpjvnzswhmbzgdwzhvbgkiddhirgljbflgvyksxgnsvztcywpvutqryzdeerlildbzmtsgnebvsjetdnfgikrbsktbrdamfccvcptfaaklmcaqmglneebpdxkvcwwpndrjqnpqgbgihsfeotgggkdbvcdwfjanvafvxsvvhzyncwlmqqsmledzfnxxfyvcmhtjreykqlrfiqlsqzraqgtmocijejneeezqxbtomkwugapwesrinfiaxwxradnuvbyssqkznwwpsbgatlsxfhpcidfgzrc"));
	OutString(s.longestDupSubstring("banana"));
	OutString(s.longestDupSubstring("abcd"));
	OutString(s.longestDupSubstring("aaaaa"));
}
