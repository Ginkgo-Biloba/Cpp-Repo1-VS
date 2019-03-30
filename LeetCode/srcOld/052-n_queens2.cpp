#include <iostream>

/* 计算 N 皇后解的个数 */
class Queens
{
public:
	static int const dimMax = sizeof(size_t) * 8;
	static size_t const szt1 = static_cast<size_t>(1u);
	int dim;
	size_t nAns, limit;

	Queens(int d = 0) : dim(d) {}

	void valid(size_t row, size_t ld, size_t rd)
	{
		size_t pos, p;
		if (row != limit)
		{
			pos = limit & (~(row | ld | rd)); // 得到可以放置皇后的位置 (二进制位为 1)
			while (pos)
			{
				p = pos & (~pos + szt1); // 拿到二进制中最右边一个 1
				pos -= p; // 去掉现在要考虑的这个位置
				valid(row | p, (ld | p) << 1, (rd | p) >> 1);
			}
		}
		else nAns++; // row 的所有 (dim) 位都是 1，说明 dim 个皇后都放进去了
	}

	void solve()
	{
		nAns = 0;
		if (dim == 1) { nAns = 1; return; } // 1 个皇后，解的个数为 1
		// 0 2 3 个皇后都没有解；皇后个数再多就没法用位运算玩了，参见 051-n_queens
		if (dim < 0 || dim > dimMax) return;
		limit = (szt1 << dim) - szt1; // 后 dim 位全 1
		valid(0u, 0u, 0u);
	}
};

int main()
{
	int dim;
	std::cin >> dim;
	Queens qs(dim);
	qs.solve();
	std::cout << "Total " << qs.nAns << " solution(s)\n";
	return 0;
}
