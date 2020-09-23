#include "leetcode.hpp"

/* 686. 重复叠加字符串匹配

给定两个字符串 A 和 B, 寻找重复叠加字符串A的最小次数，使得字符串B成为叠加后的字符串A的子串，如果不存在则返回 -1。

举个例子，A = "abcd"，B = "cdabcdab"。

答案为 3， 因为 A 重复叠加三遍后为 “abcdabcdabcd”，此时 B 是其子串；A 重复叠加两遍后为"abcdabcd"，B 并不是其子串。

注意:
 A 与 B 字符串的长度在1和10000区间范围内。
*/


int repeatedStringMatch(string const& A, string const& B)
{
	int a = static_cast<int>(A.size());
	int b = static_cast<int>(B.size());
	int r = (b + a - 1) / a;
	string C;
	C.reserve((r + 1) * a);
	for (int i = 0; i < r; ++i)
		C.append(A);
	for (int i = 0; i < 2; ++i)
	{
		if (C.find(B) != string::npos)
			return i + r;
		C.append(A);
	}
	return -1;
}


int main()
{
	OutExpr(repeatedStringMatch("abcd", "cdabcdab"), "%d");
	OutExpr(repeatedStringMatch("abce", "cdabcdab"), "%d");
}
