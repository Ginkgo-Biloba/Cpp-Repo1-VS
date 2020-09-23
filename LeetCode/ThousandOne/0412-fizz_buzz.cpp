#include "leetcode.hpp"

vector<string> fizzBuzz(int n)
{
	string s3("Fizz");
	string s5("Buzz");
	string s15 = s3 + s5;
	char buf[32];
	vector<string> ans;
	ans.reserve(n);

	for (int i = 0; i < n;)
	{
		++i;
		if (i % 15 == 0)
			ans.push_back(s15);
		else if (i % 5 == 0)
			ans.push_back(s5);
		else if (i % 3 == 0)
			ans.push_back(s3);
		else
		{
			int len = sprintf(buf, "%d", i);
			ans.push_back(string(buf, len));
		}
	}

	return ans;
}

int main()
{
	output(fizzBuzz(17), "\n", "fizzBuzz");
}
