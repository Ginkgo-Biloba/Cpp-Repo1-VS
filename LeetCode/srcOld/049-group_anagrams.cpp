#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
typedef std::vector<std::string> vecstr;

/* 给定一堆单词，把变位词放一块儿 */
std::vector<vecstr> anagrams(vecstr const& strs)
{
	size_t i = 0u, k, sz = strs.size();
	std::vector<std::pair<std::string, std::string>> ss;
	ss.reserve(sz);
	std::vector<vecstr> ans;
	std::string prev;
	for (std::string const& s : strs)
	{
		prev = s;
		std::sort(prev.begin(), prev.end());
		ss.emplace_back(prev, s);
	}
	std::sort(ss.begin(), ss.end());

	while (i < sz)
	{
		vecstr vs;
		vs.push_back(ss[i].second);
		for (k = i + 1u; k < sz; k++)
		{
			if (ss[i].first != ss[k].first)
				break;
			else
				vs.push_back(ss[k].second);
		}
		i = k;
		ans.push_back(std::move(vs));
	}
	return ans;
}


int main()
{
	vecstr strs {"eat", "tea", "tan", "ate", "nat", "bat"};
	std::vector<vecstr> ans = anagrams(strs);
	for (vecstr const& vs : ans)
	{
		for (std::string const& s : vs)
			std::cout << s << "  ";
		std::cout << "\n";
	}
	return 0;
}