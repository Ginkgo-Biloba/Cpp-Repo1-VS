#include "../srcOld/utility.hpp"


string convertToTitle1(int n)
{
	if (n == 0)
		return "";
	n--;
	char s = (n % 26) + 'A';
	n /= 26;
	auto res = convertToTitle1(n);
	res.push_back(s);
	return res;

}


string convertToTitle2(int n)
{
	string ans;
	int m;
	while (n > 0)
	{
		m = n % 26;
		if (m == 0)
		{
			ans.push_back(static_cast<char>('Z'));
			n = (n - 26) / 26;
		}
		else
		{
			ans.push_back(static_cast<char>('A' + m - 1));
			n /= 26;
		}
	}

	std::reverse(ans.begin(), ans.end());

	return ans;
}


string convertToTitle(int n)
{
	string ans;
	int base = 26;

	while (n)
	{
		int cur = (n - 1) % 26;
		ans.push_back(static_cast<char>(cur + 'A'));
		n = (n - 1) / base;
	}
	std::reverse(ans.begin(), ans.end());

	return ans;
}



int titleToNumber(string s)
{
	int ans = 0;
	for (char const c : s)
		ans = ans * 26 + (c - 'A') + 1;
	return ans;
}



int main()
{
	string ans = convertToTitle(26);
	printf("%1s = %s\n", "convertToTitle", ans.c_str());
}
