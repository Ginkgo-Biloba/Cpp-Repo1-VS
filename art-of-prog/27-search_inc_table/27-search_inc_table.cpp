#include <cstdio>
#include <cstdlib>
#include <ctime>

/**< 行列非减（杨式）矩阵查找 */
// Ref: http://taop.marchtea.com/04.02.html

/* 定位法，左闭右开区间
 * 首先直接定位到最右上角的元素，再配以二分查找
 * 比要找的数大就往左走，比要找的数小就往下走，直到找到要找的数字为止
 * 这个方法的时间复杂度 O(m + n) */
bool ys(int const* a, int const& rs, int const& cs, int const& key, int& iR, int& iC)
{
	iR = 0; iC = cs - 1;
	int const rs1 = rs - 1;
	int val = a[iR * cs + iC];
	while (true)
	{
		if (val == key)
			return true;
		else if (val < key && iR < rs1)
			++iR;  // 向下
		else if (val > key && iC > 0)
			--iC;  // 向左
		else
			return false;
		val = a[iR * cs + iC]; // 更新
	}
}

int main()
{
	int const n = 4;
	int const key = 7;
	int r; int c;
	int const a[16] = { 1, 2, 8, 9, 2, 4, 9, 12, 4, 7, 10, 13, 6, 8, 11, 15 };
	bool has6 = ys(a, n, n, key, r, c);
	printf("\nArray:");
	for (int k = 0; k < n; ++k)
	{
		int const* p = a + 4 * k;
		printf("\n\t%3d, %3d, %3d, %3d", p[0], p[1], p[2], p[3]);
	}
	if (has6)
		printf("\n%d exists at (%d, %d).", key, r, c);
	else
		printf("\n%d does not exist.", key);
	printf("\n");
	return 0;
}
