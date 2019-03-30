#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
#ifdef _MSC_VER
#include <crtdbg.h>
#pragma warning(disable: 4996)
#endif

/* 题目说可以假定唯一解 */
class Sudoku
{
public:
	static int const dim = 9;

	Sudoku() {};
	~Sudoku() {};
	void solve(FILE* fin, FILE* fout);

protected:
	struct Cell
	{
		char value; // [1, 9]，0 则说明未设定
		char numValid; // 可以填多少个 (未约束的) 数
		char constraint[dim + 1]; // 如果 constraint[v] == 1 则单元格不能填 v，10 不考虑 0

		Cell() : value(0), numValid(dim) { memset(constraint, 0, dim + 1); }
		void all(int v) { memset(constraint, v, dim + 1); }
		Cell& operator=(Cell const& rhs)
		{
			if (this != &rhs)
			{
				value = rhs.value; numValid = rhs.numValid;
				memcpy(this->constraint, rhs.constraint, dim + 1);
			}
			return (*this);
		}
	};
	struct Point
	{
		int r, c;

		Point(int rr, int cc) :r(rr), c(cc) {}
	};

private:
	Cell board[dim][dim];
	std::vector<Point> blankCell; // 空单元格列表，记录回溯状态
	bool set(int r, int c, char v);
	bool updateConstraint(int r, int c, char exv);
	bool findValForBlankCell();
	bool backtrack(int k);
};

void Sudoku::solve(FILE* fin, FILE* fout)
{
	char row[10];
	for (int r = 0; r < dim; r++)
	{
		fscanf(fin, "%9s", row);
		for (int c = 0; c < dim; c++)
		{
			if (row[c] != '.' && !set(r, c, row[c] - '0')) return; // 数独有错或不可解
		}
	}

	/* 如果没有空格子，认为给出的就是一个解 */
	/* 否则需要回溯 */
	if (!findValForBlankCell()) return;

	/* 输出 */
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
			fprintf(fout, "%hhd ", board[r][c].value);
		fprintf(fout, "\n");
	}
}

/* 设定单元格 board[r][c] 的值为 v
 * 同时传播约束到其他的单元格并推断新的可能的值*/
bool Sudoku::set(int r, int c, char v)
{
	/* 更新单元格状态 */
	Cell* bc = &(board[r][c]);
	if (bc->value == v) return true;
	if (bc->constraint[v]) return false;
	bc->all(1); // 所有数都不可填
	bc->constraint[v] = 0; // 重设状态，只有 v 可填
	bc->numValid = 1;
	bc->value = v;

	/* 传播约束 */
	int ir = r / 3 * 3, ic = c / 3 * 3;
	for (int k = 0; k < 9; k++)
	{
		if (r != k && !updateConstraint(k, c, v)) return false; // 行
		if (c != k && !updateConstraint(r, k, v)) return false; // 列
		int irk = ir + k / 3, ick = ic + (k & 0x11);
		if (irk != r && ick != c && !updateConstraint(irk, ick, v)) return false; // 块
	}

	return true;
}

/* 更新单元格 board[r][c] 的约束，通过排除所有可能的 exv
 * 如果只有一个数可用，那么函数递归回 set (退出) */
bool Sudoku::updateConstraint(int r, int c, char exv)
{
	Cell* bc = &(board[r][c]);
	if (bc->constraint[exv]) return true; // 已经排除
	if (bc->value == exv) return false; // 冲突
	bc->constraint[exv] = 1; bc->numValid--; // 设置排除
	if (bc->numValid > 1) return true; // 还有多个可填
	for (char v = 1; v <= static_cast<char>(9); v++) // 只剩一个数可填，找出它并设置
	{
		if (!(bc->constraint[v])) return set(r, c, v);
	}
	assert(false); // 正确的话，永远不可能到达这里
	return false;
}

/* 查找空单元格的值 */
bool Sudoku::findValForBlankCell()
{
	/* 查找空单元格 */
	blankCell.clear();
	for (int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++)
		{
			if (!(board[r][c].value))
				blankCell.emplace_back(r, c);
		}

	/* 通过可能填的数字个数排序，提高回溯效率 */
	std::sort(blankCell.begin(), blankCell.end(), [this](Point const& a, Point const& b) -> bool \
	{ return board[a.r][a.c].numValid < board[b.r][b.c].numValid; });
	return backtrack(0);
}

/* 发现所有索引小于 k 的空的单元格的数值 */
bool Sudoku::backtrack(int k)
{
	if (k >= static_cast<int>(blankCell.size()))
		return true;

	/* 最快的路径，只有 1 个可以填的数字 */
	int r = blankCell[k].r, c = blankCell[k].c;
	if (board[r][c].value)
		return backtrack(k + 1);

	/* 可能数字个数大于 1 的情形，记录状态快照 */
	Cell snapshot = board[r][c]; // 快照，用于回溯
	char* cst = board[r][c].constraint;
	for (char v = 1; v < static_cast<char>(9); v++)
	{
		if (!(cst[v])) // 可以填，就填一下试试
		{
			if (set(r, c, v)) // 成功填上，继续下一个，
				if (backtrack(k + 1)) return true; // 打印而不返回则输出所有解
			// 填上去不行，恢复之前的快照，直接复制比撤销操作省事 (快)
			board[r][c] = snapshot;
		}
	}
	return false;
}


int main()
{
	/*
	53..7....
	6..195...
	.98....6.
	8...6...3
	4..8.3..1
	7...2...6
	.6....28.
	...419..5
	....8..79
	*/
	Sudoku sdk;
	sdk.solve(stdin, stdout);
#ifdef _MSC_VER
	_CrtDumpMemoryLeaks(); /* 检测内存泄漏而已 */
#endif
	return 0;
}
