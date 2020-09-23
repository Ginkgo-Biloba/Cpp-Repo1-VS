#include "leetcode.hpp"

/* 1138. 字母板上的路径

我们从一块字母板上的位置 (0, 0) 出发，该坐标对应的字符为 board[0][0]。

在本题里，字母板为board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"]，如下所示。
https://assets.leetcode.com/uploads/2019/07/28/azboard.png

我们可以按下面的指令规则行动：
	如果方格存在，'U' 意味着将我们的位置上移一行；
	如果方格存在，'D' 意味着将我们的位置下移一行；
	如果方格存在，'L' 意味着将我们的位置左移一列；
	如果方格存在，'R' 意味着将我们的位置右移一列；
	'!' 会把在我们当前位置 (r, c) 的字符 board[r][c] 添加到答案中。

注意，字母板上只存在有字母的位置。

返回指令序列，用最小的行动次数让答案和目标 target 相同。你可以返回任何达成目标的路径。

示例 1：
输入：target = "leet"
输出："DDR!UURRR!!DDD!"

示例 2：
输入：target = "code"
输出："RR!DDRR!UUL!R!"

提示：
	1 <= target.length <= 100
	target 仅含有小写英文字母。
*/

// https://leetcode.com/problems/alphabet-board-path/discuss/345278/C%2B%2BJava-O(n)
// 抄的
class Solution
{
public:
	// Note that 'z' is tricky as you cannot move left or right in the last row.
	// To account for that, make sure we move up before moving right, and move left before moving down.
	string alphabetBoardPath(string target)
	{
		string A;
		int x = 0, y = 0;
		for (char t : target)
		{
			int x1 = (t - 'a') % 5, y1 = (t - 'a') / 5;
			A += string(max(0, y - y1), 'U')
				+ string(max(0, x1 - x), 'R')
				+ string(max(0, x - x1), 'L')
				+ string(max(0, y1 - y), 'D')
				+ "!";
			x = x1;
			y = y1;
		}
		return A;
	}
};


int main()
{
	Solution s;
	OutString(s.alphabetBoardPath("leet"));
}
