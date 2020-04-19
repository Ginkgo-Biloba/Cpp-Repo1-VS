#include "leetcode.hpp"

/* 1320. 二指输入的的最小距离

https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/11/leetcode_keyboard.png

二指输入法定制键盘在 XY 平面上的布局如上图所示，其中每个大写英文字母都位于某个坐标处，例如字母 A 位于坐标 (0,0)，字母 B 位于坐标 (0,1)，字母 P 位于坐标 (2,3) 且字母 Z 位于坐标 (4,1)。

给你一个待输入字符串 word，请你计算并返回在仅使用两根手指的情况下，键入该字符串需要的最小移动总距离。
坐标 (x1,y1) 和 (x2,y2) 之间的距离是 |x1 - x2| + |y1 - y2|。

注意，两根手指的起始位置是零代价的，不计入移动总距离。
你的两根手指的起始位置也不必从首字母或者前两个字母开始。

示例 1：
输入：word = "CAKE"
输出：3
解释：
使用两根手指输入 "CAKE" 的最佳方案之一是：
手指 1 在字母 'C' 上 -> 移动距离 = 0
手指 1 在字母 'A' 上 -> 移动距离 = 从字母 'C' 到字母 'A' 的距离 = 2
手指 2 在字母 'K' 上 -> 移动距离 = 0
手指 2 在字母 'E' 上 -> 移动距离 = 从字母 'K' 到字母 'E' 的距离  = 1
总距离 = 3

示例 2：
输入：word = "HAPPY"
输出：6
解释：
使用两根手指输入 "HAPPY" 的最佳方案之一是：
手指 1 在字母 'H' 上 -> 移动距离 = 0
手指 1 在字母 'A' 上 -> 移动距离 = 从字母 'H' 到字母 'A' 的距离 = 2
手指 2 在字母 'P' 上 -> 移动距离 = 0
手指 2 在字母 'P' 上 -> 移动距离 = 从字母 'P' 到字母 'P' 的距离 = 0
手指 1 在字母 'Y' 上 -> 移动距离 = 从字母 'A' 到字母 'Y' 的距离 = 4
总距离 = 6

示例 3：
输入：word = "NEW"
输出：3

示例 4：
输入：word = "YEAR"
输出：7

提示：
	2 <= word.length <= 300
	每个 word[i] 都是一个大写英文字母。
*/

// https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/discuss/477652/JavaC%2B%2BPython-1D-DP-O(1)-Space
// 抄的
class Solution
{
	int D[27][27];
	vector<int> dp, buf;

	int at(int a, int b)
	{
		return a * 27 + b;
	}

public:
	Solution()
	{
		for (int a = 0; a < 26; ++a)
		{
			int ax = a % 6, ay = a / 6;
			for (int b = 0; b < 26; ++b)
			{
				int bx = b % 6, by = b / 6;
				D[a][b] = abs(ax - bx) + abs(ay - by);
			}
			D[a][26] = 0;
		}
		for (int b = 0; b < 27; ++b)
			D[26][b] = 0;
	}

	int minimumDistance_1(string word)
	{
		dp.resize(27 * 27);
		buf.resize(dp.size());
		dp[at(26, 26)] = 0;

		int len = static_cast<int>(word.size());
		for (int i = 0; i < len; ++i)
		{
			int c = word[i] - 'A';
			dp.swap(buf);
			memset(dp.data(), 0x3f, sizeof(int) * dp.size());
			for (int a = 0; a <= 26; ++a)
				for (int b = 0; b <= 26; ++b)
				{
					dp[at(c, b)] = min(dp[at(c, b)], buf[at(a, b)] + D[a][c]);
					dp[at(a, c)] = min(dp[at(a, c)], buf[at(a, b)] + D[b][c]);
				}
		}

		int ans = 0x3f3f3f3f;
		for (int i = static_cast<int>(dp.size()) - 1; i >= 0; --i)
			ans = min(ans, dp[i]);
		return ans;
	}

	int minimumDistance(string word)
	{
		dp.assign(26U, 0);
		int len = static_cast<int>(word.size());
		int ans = 0, save = 0;
		for (int i = 0; i < len - 1; ++i)
		{
			int b = word[i] - 'A';
			int c = word[i + 1] - 'A';
			for (int a = 0; a < 26; ++a)
				dp[b] = max(dp[b], dp[a] + D[b][c] - D[a][c]);
			save = max(save, dp[b]);
			ans += D[b][c];
		}
		return ans - save;
	}
};


int main()
{
	Solution s;
	OutExpr(s.minimumDistance("CAKE"), "%d");
	OutExpr(s.minimumDistance("HAPPY"), "%d");
	OutExpr(s.minimumDistance("NEW"), "%d");
	OutExpr(s.minimumDistance("YEAR"), "%d");
}
