#include "../srcOld/utility.hpp"


int numIslands(vector<vector<char>>& grid)
{
	int const rows = static_cast<int>(grid.size());
	if (rows == 0) return 0;
	int const cols = static_cast<int>(grid[0].size());
	if (cols == 0) return 0;

	// nums 标签多少个，count 最后的独立连通域个数
	int nums = 0, count = 0;
	// 第 0 个不用，标签数肯定不会超过一半
	int const szBuffer = (rows * cols) * sizeof(int);
	int* labels = static_cast<int*>(malloc(szBuffer));
	int* parents = static_cast<int*>(malloc(szBuffer));
	memset(labels, 0x00, szBuffer);
	memset(parents, 0x00, szBuffer);
	char const* G = grid[0].data();
	int const* prevL; int* L = labels;

	L[0] = G[0] - '0';
	if (L[0])
	{
		++nums;
		L[0] = nums;
		parents[nums] = nums;

	}
	for (int c = 1; c < cols; ++c)
	{
		L[c] = G[c] - '0';
		if (L[c] == 0) continue;
		if (L[c - 1])
			L[c] = L[c - 1];
		else
		{
			++nums;
			L[c] = nums;
			parents[nums] = nums;
		}
	}

	for (int r = 1; r < rows; ++r)
	{
		G = grid[r].data();
		L = labels + r * cols;
		prevL = L - cols;

		L[0] = G[0] - '0';
		if (L[0])
		{
			if (prevL[0])
				L[0] = prevL[0];
			else
			{
				++nums;
				L[0] = nums;
				parents[nums] = nums;
			}
		}

		for (int c = 1; c < cols; ++c)
		{
			L[c] = G[c] - '0';
			if (L[c] == 0) continue;

			int left = L[c - 1], up = prevL[c];
			if (left == 0 && up == 0)
			{
				++nums;
				L[c] = nums;
				parents[nums] = nums;
			}
			else if (left == 0 && up != 0)
				L[c] = up;
			else if (left != 0 && up == 0)
				L[c] = left;
			else if (left == up) // 可以不要
				L[c] = left;
			else
			{
				int parL = parents[left], parU = parents[up];
				while (parL != parents[parL]) parL = parents[parL];
				while (parU != parents[parU]) parU = parents[parU];
				// 分别拿出较小值和较大值
				if (parL > parU) std::swap(parL, parU);

				L[c] = parL;
				parents[left] = parents[up] = parents[parU] = parL;
			}
		}
	}

	// 发现标签数量，并更新父节点。本题不用更新的
	for (int i = 1; i <= nums; ++i)
	{
		if (parents[i] == i)
		{
			++count;
			parents[i] = count; // 这一步可以筛选掉空着的标号，本题不用
		}
		else
		{
			int p = parents[i];
			while (p != parents[p]) p = parents[p];
			parents[i] = p;
		}
	}

	// 更新标签图。本题不用更新的
	for (int c = rows * cols; c--;)
		labels[c] = parents[labels[c]];

	// for (int c = 0; c < rows * cols; ++c)
	// printf("%d, ", labels[c]);

	free(labels);
	free(parents);
	return count;
}


int main()
{
	vector<vector<char>> grid = {
		{ '1', '0', '1', '1', '1' },
		{ '1', '0', '1', '0', '1' },
		{ '1', '1', '1', '0', '1' }
	};
	grid = {
		{ '1', '0', '1', '1', '0', '0', '1', '0', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1', '0' },
		{ '0', '1', '0', '0', '1', '0', '1', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1' },
		{ '1', '0', '0', '1', '0', '1', '0', '1', '0', '1', '1', '0', '1', '1', '1', '0', '0', '1', '1', '0' },
		{ '0', '1', '1', '0', '0', '1', '1', '0', '1', '1', '1', '1', '0', '0', '1', '0', '0', '0', '1', '1' },
		{ '1', '1', '0', '1', '0', '0', '1', '0', '0', '0', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1' },
		{ '0', '0', '0', '0', '1', '0', '1', '1', '0', '0', '1', '0', '0', '1', '0', '1', '1', '1', '1', '0' },
		{ '1', '0', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '0', '1', '1', '1', '0', '0', '1', '0' },
		{ '0', '1', '1', '0', '0', '0', '1', '0', '0', '1', '0', '1', '1', '1', '0', '0', '1', '1', '0', '1' },
		{ '0', '0', '0', '0', '1', '1', '0', '1', '0', '0', '1', '1', '0', '1', '0', '0', '1', '0', '1', '0' },
		{ '0', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '1', '0' },
		{ '1', '0', '1', '0', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '1', '0', '1', '0', '1', '1' },
		{ '0', '0', '1', '1', '1', '1', '0', '1', '1', '1', '0', '1', '0', '0', '0', '1', '1', '1', '0', '1' },
		{ '1', '1', '1', '0', '0', '0', '0', '0', '1', '1', '0', '1', '1', '1', '0', '1', '1', '1', '1', '0' },
		{ '0', '0', '1', '1', '1', '0', '0', '1', '0', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0' },
		{ '0', '0', '0', '1', '1', '0', '0', '0', '0', '1', '1', '0', '1', '0', '0', '1', '1', '1', '1', '1' },
		{ '0', '1', '1', '1', '0', '1', '0', '0', '1', '1', '1', '1', '1', '0', '1', '1', '1', '0', '0', '1' },
		{ '0', '0', '0', '0', '1', '1', '1', '1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1', '1', '0' },
		{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0', '1', '1', '1', '1', '1', '1' },
		{ '0', '1', '0', '0', '1', '0', '0', '1', '1', '1', '1', '1', '1', '0', '1', '0', '1', '1', '1', '1' },
		{ '0', '0', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '1', '1', '0', '1', '1', '0' }
	};
	int ans = numIslands(grid);
	printf("%1s = %d\n", "numIslands", ans);
}
