#include "leetcode.hpp"

/* 1311. 获取你好友已观看的视频

有 n 个人，每个人都有一个  0 到 n-1 的唯一 id 。

给你数组 watchedVideos  和 friends ，其中 watchedVideos[i]  和 friends[i] 分别表示 id = i 的人观看过的视频列表和他的好友列表。

Level 1 的视频包含所有你好友观看过的视频，level 2 的视频包含所有你好友的好友观看过的视频，以此类推。一般的，Level 为 k 的视频包含所有从你出发，最短距离为 k 的好友观看过的视频。

给定你的 id  和一个 level 值，请你找出所有指定 level 的视频，并将它们按观看频率升序返回。
如果有频率相同的视频，请将它们按字母顺序从小到大排列。

示例 1：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/03/leetcode_friends_1.png
输入：
watchedVideos = [["A","B"],["C"],["B","C"],["D"]],
friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 1
输出：["B","C"]
解释：
你的 id 为 0（绿色），你的朋友包括（黄色）：
id 为 1 -> watchedVideos = ["C"]
id 为 2 -> watchedVideos = ["B","C"]
你朋友观看过视频的频率为：
B -> 1
C -> 2

示例 2：
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/03/leetcode_friends_2.png
输入：
watchedVideos = [["A","B"],["C"],["B","C"],["D"]],
friends = [[1,2],[0,3],[0,3],[1,2]], id = 0, level = 2
输出：["D"]
解释：
你的 id 为 0（绿色），你朋友的朋友只有一个人，他的 id 为 3（黄色）。

提示：
	n == watchedVideos.length == friends.length
	2 <= n <= 100
	1 <= watchedVideos[i].length <= 100
	1 <= watchedVideos[i][j].length <= 8
	0 <= friends[i].length < n
	0 <= friends[i][j] < n
	0 <= id < n
	1 <= level < n
	如果 friends[i] 包含 j ，那么 friends[j] 包含 i
*/


vector<string> watchedVideosByFriends(
	vector<vector<string>>& watchedVideos,
	vector<vector<int>>& friends,
	int id, int level)
{
	int len = static_cast<int>(friends.size());
	vector<char> visit(len);
	vector<int> current, nextloop;
	current.push_back(id);
	visit[id] = 1;

	for (; !current.empty() && (level > 0); --level)
	{
		nextloop.clear();
		for (int cur : current)
			for (int f : friends[cur])
				if (!(visit[f]))
				{
					nextloop.push_back(f);
					visit[f] = 1;
				}
		nextloop.swap(current);
	}

	unordered_map<string, int> video;
	for (int cur : current)
	{
		for (string const& s : watchedVideos[cur])
			video[s] += 1;
	}

	vector<pair<int, string>> cand;
	for (auto const& kv : video)
		cand.emplace_back(kv.second, kv.first);
	sort(cand.begin(), cand.end());

	vector<string> ans;
	for (auto const& p : cand)
		ans.push_back(p.second);
	return ans;
}


int main()
{}
