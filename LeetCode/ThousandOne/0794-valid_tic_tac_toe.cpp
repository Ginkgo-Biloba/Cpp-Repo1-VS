#include "leetcode.hpp"

/* 794. 有效的井字游戏

用字符串数组作为井字游戏的游戏板 board。
当且仅当在井字游戏过程中，玩家有可能将字符放置成游戏板所显示的状态时，才返回 true。

该游戏板是一个 3 x 3 数组，由字符 " "，"X" 和 "O" 组成。字符 " " 代表一个空位。

以下是井字游戏的规则：
	玩家轮流将字符放入空位（" "）中。
	第一个玩家总是放字符 “X”，且第二个玩家总是放字符 “O”。
	“X” 和 “O” 只允许放置在空位中，不允许对已放有字符的位置进行填充。
	当有 3 个相同（且非空）的字符填充任何行、列或对角线时，游戏结束。
	当所有位置非空时，也算为游戏结束。
	如果游戏结束，玩家不允许再放置字符。

示例 1:
输入: board = ["O  ", "   ", "   "]
输出: false
解释: 第一个玩家总是放置“X”。

示例 2:
输入: board = ["XOX", " X ", "   "]
输出: false
解释: 玩家应该是轮流放置的。

示例 3:
输入: board = ["XXX", "   ", "OOO"]
输出: false

示例 4:
输入: board = ["XOX", "O O", "XOX"]
输出: true

说明:
	游戏板 board 是长度为 3 的字符串数组，其中每个字符串 board[i] 的长度为 3。
	board[i][j] 是集合 {" ", "X", "O"} 中的一个字符。
*/

// https://leetcode.com/problems/valid-tic-tac-toe-state/discuss/117580/Straightforward-Java-solution-with-explaination
// 抄的
bool validTicTacToe(vector<string>& board)
{
	int turn = 0;
	bool xwin = false, owin = false;
	int row[3] = { 0 }, col[3] = { 0 };
	int diag = 0, anti = 0;

	for (int h = 0; h < 3; ++h)
		for (int w = 0; w < 3; ++w)
		{
			if (board[h][w] == 'X')
			{
				++turn;
				++row[h];
				++col[w];
				diag += (h == w);
				anti += (h + w == 2);
			}
			else if (board[h][w] == 'O')
			{
				--turn;
				--row[h];
				--col[w];
				diag -= (h == w);
				anti -= (h + w == 2);
			}
		}

	xwin = diag == 3 || anti == 3
		|| row[0] == 3 || row[1] == 3 || row[2] == 3
		|| col[0] == 3 || col[1] == 3 || col[2] == 3;
	owin = diag == -3 || anti == -3
		|| row[0] == -3 || row[1] == -3 || row[2] == -3
		|| col[0] == -3 || col[1] == -3 || col[2] == -3;

	if ((xwin && turn == 0) || (owin && turn == 1))
		return false;

	return (turn == 0 || turn == 1) && !(xwin && owin);
}


int main()
{
	vector<string>
		b0 = { "O  ", "   ", "   " },
		b1 = { "XOX", " X ", "   " },
		b2 = { "XXX", "   ", "OOO" },
		b3 = { "XOX", "O O", "XOX" };
	OutBool(validTicTacToe(b0));
	OutBool(validTicTacToe(b1));
	OutBool(validTicTacToe(b2));
	OutBool(validTicTacToe(b3));
}
