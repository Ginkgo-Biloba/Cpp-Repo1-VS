#include "leetcode.hpp"

/* 920. 播放列表的数量

你的音乐播放器里有 N 首不同的歌，在旅途中，你的旅伴想要听 L 首歌（不一定不同，即，允许歌曲重复）。请你为她按如下规则创建一个播放列表：
	每首歌至少播放一次。
	一首歌只有在其他 K 首歌播放完之后才能再次播放。

返回可以满足要求的播放列表的数量。由于答案可能非常大，请返回它模 10^9 + 7 的结果。


示例 1：
输入：N = 3, L = 3, K = 1
输出：6
解释：有 6 种可能的播放列表。[1, 2, 3]，[1, 3, 2]，[2, 1, 3]，[2, 3, 1]，[3, 1, 2]，[3, 2, 1].

示例 2：
输入：N = 2, L = 3, K = 0
输出：6
解释：有 6 种可能的播放列表。[1, 1, 2]，[1, 2, 1]，[2, 1, 1]，[2, 2, 1]，[2, 1, 2]，[1, 2, 2]

示例 3：
输入：N = 2, L = 3, K = 1
输出：2
解释：有 2 种可能的播放列表。[1, 2, 1]，[2, 1, 2]

提示：
	0 <= K < N <= L <= 100
*/


// https://leetcode.com/problems/number-of-music-playlists/discuss/180338/DP-solution-that-is-Easy-to-understand
// 抄的
int numMusicPlaylists(int N, int L, int K)
{
	int64_t const Mod = 1e9 + 7;
	int64_t dp[101][101];
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int l = 1; l <= L; ++l)
		for (int n = 1; n <= N; ++n)
		{
			// 新歌
			int64_t x = (dp[l - 1][n - 1] * (N - (n - 1))) % Mod;
			// 旧歌
			if (n > K)
				x += (dp[l - 1][n] * (n - K));
			dp[l][n] = x % Mod;
		}
	return static_cast<int>(dp[L][N]);
}

int main()
{
	OutExpr(numMusicPlaylists(3, 3, 1), "%d");
	OutExpr(numMusicPlaylists(2, 3, 0), "%d");
	OutExpr(numMusicPlaylists(2, 3, 1), "%d");
}
