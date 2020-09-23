#include "leetcode.hpp"

/* 273. 整数转换英文表示

将非负整数转换为其对应的英文表示。可以保证给定输入小于 231 - 1 。

示例 1:
输入: 123
输出: "One Hundred Twenty Three"

示例 2:
输入: 12345
输出: "Twelve Thousand Three Hundred Forty Five"

示例 3:
输入: 1234567
输出: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

示例 4:
输入: 1234567891
输出: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
*/

static string const LESS20[20] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
static string const TENS[10] = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
static string const THOUSANDS[4] = { "", "Thousand", "Million", "Billion" };

// https://leetcode.com/problems/integer-to-english-words/discuss/70625/My-clean-Java-solution-very-easy-to-understand/72850
// 抄的
class Solution
{
	string Less1000(int num)
	{
		if (num == 0) return "";
		if (num < 20) return LESS20[num] + " ";
		if (num < 100) return TENS[num / 10] + " " + Less1000(num % 10);
		return LESS20[num / 100] + " Hundred " + Less1000(num % 100);
	}

	string numberToString(int num, int i)
	{
		if (num == 0) return "";
		if (num % 1000 == 0) return numberToString(num / 1000, i + 1);
		return numberToString(num / 1000, i + 1) + Less1000(num % 1000) + THOUSANDS[i] + " ";
	}

public:
	string numberToWords(int num)
	{
		if (num == 0) return "Zero";
		string res = numberToString(num, 0);
		return res.substr(0, res.find_last_not_of(' ') + 1);
	}
};


int main()
{
	Solution s;
	OutString(s.numberToWords(123));
	OutString(s.numberToWords(12345));
	OutString(s.numberToWords(1234567));
	OutString(s.numberToWords(1234567891));
}
