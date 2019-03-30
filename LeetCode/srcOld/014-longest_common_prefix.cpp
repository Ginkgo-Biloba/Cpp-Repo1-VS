#include <vector>
#include <string>
#include <iostream>
using namespace std;

string lcp(vector<string> const& strs)
{
	string ans;
	size_t i, j, sz2, sz1 = strs.size();
	if (sz1 == 0u)
		return ans;
	ans = strs[0];
	for (i = 1u; i < sz1; i++)
	{
		sz2 = strs[i].size(); j = ans.size();
		if (sz2 > j) sz2 = j;
		for (j = 0u; j < sz2; j++)
			if (strs[i][j] != ans[j])
				break;
		ans.erase(j);
	}
	return ans;
}

int main()
{
	vector<string> strs;
	string ans;
	while (true)
	{
		cin >> ans;
		if (ans[0] == 'q') break;
		else strs.push_back(ans);
	}
	ans = lcp(strs);
	cout << ans << "\n";
	return 0;
}