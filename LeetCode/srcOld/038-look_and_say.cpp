#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;

string nthlas(int n)
{
	string ans("1"), prev;
	if (n < 1) return prev;
	size_t len, pos, i;
	char c;
	for (; n > 1; n--)
	{
		ans.swap(prev);
		ans.clear();
		i = pos = 0u;
		len = prev.length();
		while (i < len)
		{
			c = prev.at(i);
			pos = prev.find_first_not_of(c, i + 1);
			if (pos == string::npos) pos = len; // 到头就退出
			ans += std::to_string(pos - i);
			ans.push_back(c);
			i = pos;
		}
	}
	return ans;
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	for (int i = 0; i < 20; i++)
		std::cout << i << ": " <<  nthlas(i) << "\n";
	return 0;
}
