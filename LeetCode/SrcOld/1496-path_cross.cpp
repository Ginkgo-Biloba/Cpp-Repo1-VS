#include "leetcode.hpp"

/* 1496. 判断路径是否相交

给你一个字符串 path，其中 path[i] 的值可以是 'N'、'S'、'E' 或者 'W'，分别表示向北、向南、向东、向西移动一个单位。

机器人从二维平面上的原点 (0, 0) 处开始出发，按 path 所指示的路径行走。

如果路径在任何位置上出现相交的情况，也就是走到之前已经走过的位置，请返回 True ；否则，返回 False 。

示例 1：
https://assets.leetcode.com/uploads/2020/06/10/screen-shot-2020-06-10-at-123929-pm.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/06/28/screen-shot-2020-06-10-at-123929-pm.png
输入：path = "NES"
输出：false
解释：该路径没有在任何位置相交。

示例 2：
https://assets.leetcode.com/uploads/2020/06/10/screen-shot-2020-06-10-at-123843-pm.png
https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/06/28/screen-shot-2020-06-10-at-123843-pm.png
输入：path = "NESWW"
输出：true
解释：该路径经过原点两次。

提示：
	1 <= path.length <= 10^4
	path 仅由 {'N', 'S', 'E', 'W} 中的字符组成
*/

bool isPathCrossing(string path)
{
	int x = 0, y = 0, k = 0;
	unordered_set<int> seen;
	seen.insert(0);
	for (char c : path)
	{
		switch (c)
		{
		case 'N': y += 1; break;
		case 'E': x += 1; break;
		case 'S': y -= 1; break;
		case 'W': x -= 1; break;
		}
		k = x * 10000 + y;
		if (!(seen.insert(k).second))
			return true;
	}
	return false;
}

int main()
{
	OutBool(isPathCrossing("NES"));
	OutBool(isPathCrossing("NESWW"));
}
