#include "leetcode.hpp"

/* 1268. 搜索推荐系统

给你一个产品数组 products 和一个字符串 searchWord ，products  数组中每个产品都是一个字符串。

请你设计一个推荐系统，在依次输入单词 searchWord 的每一个字母后，推荐 products 数组中前缀与 searchWord 相同的最多三个产品。如果前缀相同的可推荐产品超过三个，请按字典序返回最小的三个。

请你以二维列表的形式，返回在输入 searchWord 每个字母后相应的推荐产品的列表。

示例 1：
输入：
products = ["mobile","mouse","moneypot","monitor","mousepad"],
searchWord = "mouse"
输出：[
	["mobile","moneypot","monitor"],
	["mobile","moneypot","monitor"],
	["mouse","mousepad"],
	["mouse","mousepad"],
	["mouse","mousepad"],
]
解释：按字典序排序后的产品列表是 ["mobile","moneypot","monitor","mouse","mousepad"]
输入 m 和 mo，由于所有产品的前缀都相同，所以系统返回字典序最小的三个产品 ["mobile","moneypot","monitor"]
输入 mou， mous 和 mouse 后系统都返回 ["mouse","mousepad"]

示例 2：
输入：products = ["havana"], searchWord = "havana"
输出：[["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]

示例 3：
输入：products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
输出：[["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]

示例 4：
输入：products = ["havana"], searchWord = "tatiana"
输出：[[],[],[],[],[],[],[]]

提示：
	1 <= products.length <= 1000
	1 <= Σ products[i].length <= 2 * 10^4
	products[i] 中所有的字符都是小写英文字母。
	1 <= searchWord.length <= 1000
	searchWord 中所有字符都是小写英文字母。
*/

vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord)
{
	int prlen = static_cast<int>(products.size());
	int swlen = static_cast<int>(searchWord.size());
	int ipr = 0, cmp = 1;
	vector<vector<string>> R(swlen);
	sort(products.begin(), products.end());
	for (int i = 0; i < swlen; ++i)
	{
		for (; ipr < prlen; ++ipr)
		{
			cmp = strncmp(products[ipr].c_str(), searchWord.c_str(), i + 1);
			if (cmp >= 0)
				break;
		}
		if ((cmp > 0) || (ipr == prlen))
			break;
		R[i].push_back(products[ipr]);
		for (int k = ipr + 1; k < prlen; ++k)
		{
			cmp = strncmp(products[k].c_str(), searchWord.c_str(), i + 1);
			if ((k > ipr + 2) || (cmp > 0))
				break;
			R[i].push_back(products[k]);
		}
	}
	return R;
}


int main()
{
	vector<string> p = { "bags", "baggage", "banner", "box", "cloths" };
	vector<vector<string>> r = suggestedProducts(p, "bags");
}
