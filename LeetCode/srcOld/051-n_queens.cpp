#include <string>
#include <vector>
#include <iostream>
using std::vector;
using std::string;
using std::ostream;

/* 求解 N 皇后问题的所有解 */
/* http://blog.csdn.net/hackbuteer1/article/details/6657109 */
class Queens
{
public:
	static char const nplace = -1; // 表示空值
	int dim;
	vector<vector<string>> ans;
	vector<string> queen;
	string checkboard;

	Queens(int d) : dim(d) {}

	char valid(int row, int col)
	{
		for (int r = 0; r < row; r++)
		{
			if (checkboard[r] == col || (row - r == abs(checkboard[r] - col)))
				return (char)(0);
		}
		return (char)(1);
	}

	void print(ostream& os)
	{
		queen.resize(dim, std::string(dim, '-'));
		for (int r = 0; r < dim; r++)
		{
			std::fill(queen[r].begin(), queen[r].end(), '-');
			queen[r][checkboard[r]] = 'x';
		}
		ans.push_back(queen);
		/* 输出 */
		os << "\nSolution " << ans.size() << ":\n";
		for (string const& str : queen)
			os << str << "\n";
	}

	void solve(ostream& os)
	{
		ans.clear();
		if (dim == 1)
		{
			os << "\nSolution 1:\nx\n";
			ans.push_back(vector<string>{string("x")});
			return;
		}
		if (dim < 4) return; // 已知 0 2 3 个皇后都没有解

		checkboard.clear(); checkboard.resize(dim, nplace);
		int r = 0, c = 0;
		while (r < dim)
		{
			/* 放置这一行，探测每一列 */
			while (c < dim)
			{
				if (valid(r, c)) // 可放置
				{
					checkboard[r] = (char)(c); // 放置
					c = 0; break; // 第 r 行放置后，需要继续探测下一行
				}
				else c++; // 不能放置则探测下一列
			}

			/* 没有找到可以放置皇后的位置 */
			if (checkboard[r] == nplace)
			{
				if (r == 0) break; // 回溯到第一行还不行，说明已经找过所有解
				else
				{
					r--; // 继续回溯上一行
					c = checkboard[r] + 1; // 从上一行的皇后下一列开始探测
					checkboard[r] = nplace; // 清除位置
				}
			}

			/* 最后一行找到一个位置，说明找到一个结果，存起来并打印 */
			else if (r == dim - 1)
			{
				print(os);
				checkboard[r] = nplace; // 清除当前行
				r--; // 从最后一行的下一列继续探测肯定不行，所以是上一行
				c = checkboard[r] + 1; // 上一行的下一个位置
				checkboard[r] = nplace; // 清除位置
			}

			else r++; // 继续探测下一行
		}
	}
};

int main()
{
	int dim;
	std::cin >> dim;
	Queens qs(dim);
	qs.solve(std::cout);
	return 0;
}