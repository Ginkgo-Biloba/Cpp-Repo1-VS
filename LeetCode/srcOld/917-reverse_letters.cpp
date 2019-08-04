#include "leetcode.hpp"


string reverseOnlyLetters(string& s)
{
	int const len = static_cast<int>(s.length());
	int l = 0, r = len - 1;
	if (len < 2) return s;
	
	while (l < r)
	{
		while ((l < r) && !isalpha(s[l])) ++l;
		while ((l < r) && !isalpha(s[r])) --r;
		if (isalpha(s[l]) && isalpha(s[r]))
			std::swap(s[l], s[r]);
		++l; --r;
	}

	return s;
}

int main()
{
	string s("Test1ng-Leet=code-Q!");
	printf("%1s = %s\n", "reverseOnlyLetters", reverseOnlyLetters(s).c_str());
}
