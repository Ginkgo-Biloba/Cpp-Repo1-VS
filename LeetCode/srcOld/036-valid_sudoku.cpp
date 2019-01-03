#include <cstdio>
#include <cstdlib>
#include <cstring>

char isValid(char** board, int row, int col)
{
	char ans = 1;
	int r, c, num, b;
	char vR[9][9]; memset(vR, 0, 81); /* 行 */
	char vC[9][9]; memset(vC, 0, 81); /* 列 */
	char vB[9][9]; memset(vB, 0, 81); /* 块 */

	for (r = 0; r < row && ans; r++)
		for (c = 0; c < col; c++)
		{
			if (board[r][c] != '.')
			{
				num = board[r][c] - '0' - 1; b = r / 3 * 3 + c / 3;
				if (vR[r][num] || vC[c][num] || vB[b][num])
				{ ans = 0; break; }
				vR[r][num] = vC[c][num] = vB[b][num] = 1;
			}
		}
	return ans;
}

int main()
{
	char* board[9];
	board[0] = "53..7...."; board[1] = "6..195..."; board[2] = ".98....6.";
	board[3] = "8...6...3"; board[4] = "4..8.3..1"; board[5] = "7...2...6";
	board[6] = ".6....28."; board[7] = "...419..5"; board[8] = "....8..79";
	char ans = isValid(board, 9, 9);
	fprintf(stdout, "%d\n", ans);
	return 0;
}
