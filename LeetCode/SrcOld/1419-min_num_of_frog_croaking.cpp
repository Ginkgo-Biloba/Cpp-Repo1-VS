#include "leetcode.hpp"

/* 1419. 数青蛙

给你一个字符串 croakOfFrogs，它表示不同青蛙发出的蛙鸣声（字符串 "croak" ）的组合。
由于同一时间可以有多只青蛙呱呱作响，所以 croakOfFrogs 中会混合多个 “croak” 。
请你返回模拟字符串中所有蛙鸣所需不同青蛙的最少数目。

注意：要想发出蛙鸣 "croak"，青蛙必须 依序 输出 ‘c’, ’r’, ’o’, ’a’, ’k’ 这 5 个字母。
如果没有输出全部五个字母，那么它就不会发出声音。

如果字符串 croakOfFrogs 不是由若干有效的 "croak" 字符混合而成，请返回 -1 。

示例 1：
输入：croakOfFrogs = "croakcroak"
输出：1
解释：一只青蛙 “呱呱” 两次

示例 2：
输入：croakOfFrogs = "crcoakroak"
输出：2
解释：最少需要两只青蛙，“呱呱” 声用黑体标注
第一只青蛙 "crcoakroak"
第二只青蛙 "crcoakroak"

示例 3：
输入：croakOfFrogs = "croakcrook"
输出：-1
解释：给出的字符串不是 "croak" 的有效组合。

示例 4：
输入：croakOfFrogs = "croakcroa"
输出：-1

提示：
	1 <= croakOfFrogs.length <= 10^5
	字符串中的字符只有 'c', 'r', 'o', 'a' 或者 'k'
*/

int minNumberOfFrogs_Org(string S)
{
	string croak("croak");
	int count[128] = { 0 };
	int len = static_cast<int>(S.size());
	vector<int> pos;
	for (int i = 0; i < len; ++i)
	{
		count[S[i]] += 1;
		if (S[i] == 'c')
			pos.push_back(i);
	}
	if ((count['c'] != count['r'])
		|| (count['c'] != count['o'])
		|| (count['c'] != count['a'])
		|| (count['c'] != count['k']))
		return -1;

	int need = 0;
	memset(count, 0, sizeof(count));
	for (int i = 0; i < len; ++i)
	{
		if (S[i] == 'k')
		{
			count['c'] -= 1;
			count['r'] -= 1;
			count['o'] -= 1;
			count['a'] -= 1;
		}
		else
			count[S[i]] += 1;
		if (count['c'] >= count['r']
			&& count['r'] >= count['o']
			&& count['o'] >= count['a'])
			;
		else
			return -1;
		need = max(need, count['c']);
	}
	for (char c : croak)
	{
		if (count[c] != 0)
			return -1;
	}
	return need;
}

int minNumberOfFrogs(string S)
{
	int num[128] = { 0 };
	char pre[128] = { 0 };
	pre['c'] = 1;
	pre['r'] = 'c';
	pre['o'] = 'r';
	pre['a'] = 'o';
	pre['k'] = 'a';
	num[1] = INT_MAX;

	int ans = 0, cur = 0;
	int len = static_cast<int>(S.size());
	for (int i = 0; i < len; ++i)
	{
		char b = S[i];
		char a = pre[b];
		num[b] += 1;
		num[a] -= 1;
		cur += (b == 'c');
		cur -= (b == 'k');
		ans = max(ans, cur);
		if (num[a] < 0)
			return -1;
	}
	num[2] = (num['c'] | num['r'] | num['o'] | num['a']);
	return num[2] ? -1 : ans;
}


int main()
{
	OutExpr(minNumberOfFrogs("croakcroak"), "%d");
	OutExpr(minNumberOfFrogs("crcoakroak"), "%d");
	OutExpr(minNumberOfFrogs("croakcrook"), "%d");
	OutExpr(minNumberOfFrogs("croakcroa"), "%d");
}
