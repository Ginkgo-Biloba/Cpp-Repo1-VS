#include "leetcode.hpp"

/* 763. 划分字母区间

字符串 S 由小写字母组成。
我们要把这个字符串划分为尽可能多的片段，同一个字母只会出现在其中的一个片段。
返回一个表示每个字符串片段的长度的列表。

示例 1:
输入: S = "ababcbacadefegdehijhklij"
输出: [9,7,8]
解释:
划分结果为 "ababcbaca", "defegde", "hijhklij"。
每个字母最多出现在一个片段中。
像 "ababcbacadefegde", "hijhklij" 的划分是错误的，因为划分的片段数较少。

注意:
	S的长度在[1, 500]之间。
	S只包含小写字母'a'到'z'。
*/

vector<int> partitionLabels(string S)
{
	int len = static_cast<int>(S.size());
	int right[26];
	int p = 0, q = 0;
	vector<int> ans;
	ans.reserve(len);
	memset(right, 0x3f, sizeof(right));
	for (int i = 0; i < len; ++i)
		right[S[i] - 'a'] = i;
	for (int i = 0; i < len; ++i)
	{
		q = std::max(q, right[S[i] - 'a']);
		if (i == q)
		{
			ans.push_back(q - p + 1);
			p = q + 1;
		}
	}
	return ans;
}


int main()
{
	output(
		partitionLabels("ababcbacadefegdehijhklij"),
		"Partition Labels");
}
