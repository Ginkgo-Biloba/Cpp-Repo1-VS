#include "../srcOld/utility.hpp"


bool wordBreak_dfs(string const& str, size_t slen, 
	unordered_set<string> const& hash, vector<char>& cannot)
{
	if (slen == str.size()) return true;
	if (cannot[slen]) return false;
	bool ans = false;
	string substr;
	for (size_t s = slen; s < str.size(); ++s)
	{
		substr.push_back(str[s]);
		if (hash.find(substr) != hash.end())
			ans = wordBreak_dfs(str, s + 1u, hash, cannot);
		if (ans) break;
	}
	if (!ans) cannot[slen] = 1;
	return ans;
}


bool wordBreak(string const& str, vector<string> const& dict)
{
	unordered_set<string> hash(dict.begin(), dict.end());
	vector<char> cannot(str.size(), 0);
	size_t const dlen = dict.size();

	bool ans = wordBreak_dfs(str, 0u, hash, cannot);
	return ans;
}


int main()
{
	vector<string> dict = { "cats", "dog", "sand", "and", "cat" };
	bool ans = wordBreak(string("cat5sdog"), dict);
	printf("%1s = %s\n", "wordBreak", (ans ? "true" : "false"));
}
