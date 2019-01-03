#include <string>
#include <vector>
#include <iostream>
using namespace std;

string const letters[10] = { "", "", "abc", "def", "ghi","jkl","mno","pqrs","tuv","wxyz" };

void dfs(string& str, string const& digits, vector<string>& ans)
{
	size_t i, sz = str.size();
	if (sz == digits.size())
	{
		ans.push_back(str);
		return;
	}
	string const& sch = letters[digits[sz] - '0'];
	sz = sch.size();
	for (i = 0u; i < sz; i++)
	{
		str.push_back(sch[i]);
		dfs(str, digits, ans);
		str.pop_back();
	}
}

/* Letter Combinations of a Phone Number */
vector<string> lcoapn(string const& digits)
{
	size_t sz = digits.size();
	vector<string> ans;
	if (sz == 0u) return ans;
	string str;
	dfs(str, digits, ans);
	return ans;
}

/* ... */
vector<string> lcoapn2(string const& digits)
{
	vector<string> ans;
	vector<string> tmp;
	if (digits.empty()) return ans;
	ans.emplace_back(string()); // seed
	size_t i, j, k, sz1, sz2, sz = digits.size();
	int num;
	for (i = 0u; i < sz; i++)
	{
		num = digits[i] - '0';
		if (num < 0 || 9 < num) break;
		string const& cand = letters[num];
		sz1 = cand.size(); sz2 = ans.size();
		if (sz1 == 0u) continue;
		tmp.clear();
		for (j = 0u; j < sz1; j++)
		{
			for (k = 0u; k < sz2; k++)
				tmp.emplace_back(ans[k] + cand[j]);
		}
		ans.swap(tmp);
	}
	return ans;
}

int main()
{
	string digits("23");
	vector<string> ans = lcoapn2(digits);
	for (string const& str : ans)
		cout << str << "\n";
	return 0;
}


