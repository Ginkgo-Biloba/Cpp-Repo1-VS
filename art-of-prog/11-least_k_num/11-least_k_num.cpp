// #include <iostream>
// #include <iomanip>
// #include <sstream>
// prinft 慢，但是 GCC 用 iostream 生成文件大
#include <cstdio>
#include <cstdlib>
#include <ctime>

/**< 寻找最小的 k 个数 */

// 交换
void swap(int* const pa, int* const pb)
{
	int i = *pa; *pa = *pb; *pb = i;
}

/* Ref: http://taop.marchtea.com/02.01.html
平均时间复杂度为 O(N) ? 的快速选择算法。
选取S中一个元素作为枢纽元 v，将集合 S-{v} 分割成 S1 和 S2，就像快速排序那样
如果k <= |S1|，那么第 k 个最小元素必然在 S1 中。在这种情况下，返回 QuickSelect(S1, k)
如果k = 1 + |S1|，那么枢纽元素就是第 k 个最小元素，即找到，直接返回它
否则，这第 k 个最小元素就在 S2 中，即 S2 中的第 (k - |S1| - 1) 个最小元素，我们递归调用并返回 QuickSelect(S2, k - |S1| - 1) */

// 将第 k 小的元素放在 a[k-1]，不包括 a[right]
void quickSelect(int* const a, int const& k, int const& left, int const& right)
{
	if (k <= 0 || k < left || right < left) exit(-1);
	if (k < left + 7 || right < left + 13) // 直接选择，13 只是有人这么用
	{
		for (int m = left; m < k; ++m)
		{
			int idx = m; int minN = a[m];
			for (int n = m + 1; n < right; ++n)
				if (minN > a[n])
				{ idx = n; minN = a[n]; }
			a[idx] = a[m];
			a[m] = minN;
		}
	}
	else // 一半的快速排序
	{
		// 首尾中 3 个数排序并选择中间数作为枢纽，存入 arr[mid]
		int const mid = (left + right) >> 1; // 真心累
		int const r1 = right - 1;
		int const r2 = right - 2;
		if (a[left] > a[mid]) swap(a + left, a + mid);
		(a[left] > a[r1]) swap(a + left, a + r1);
		if (a[mid] > a[r1]) swap(a + mid, a + r1);
		swap(a + mid, a + r2);
		int const pivot = a[r2];
		int m = left; int n = r2;
		while (true)
		{
			// while (a[++m] < pivot); // 1
			// while (a[--n] > pivot);  // 1
			// 有等号需要判断边界
			while (m < n && a[m] <= pivot) ++m; // 2
			while (m < n && a[n] >= pivot) --n; // 2
			if (m < n) swap(a + m, a + n);
			else break;
		}
		// 放回枢纽
		a[r2] = a[m]; a[m] = pivot;
		// 前后选择
		if (k == (1 + m)) return;
		else if (k <= m) quickSelect(a, k, left, m);
		else quickSelect(a, k, m + 1, right);
	}
}

// 顺便写一个快速排序，与上面高度重合，不包括 a[right]
void quickSort(int* const a, int const& left, int const& right)
{
	if (right < left) { exit(-1); }
	if (right < left + 13) // 选择排序，13 只是有人这么用
	{
		for (int m = left; m < right - 1; ++m)
		{
			int idx = m; int minN = a[m];
			for (int n = m + 1; n < right; ++n)
				if (minN > a[n])
				{ idx = n; minN = a[n]; }
			a[idx] = a[m];
			a[m] = minN;
		}
	}
	else // 递归快速排序
	{
		// 首尾中 3 个数排序并选择中间数作为枢纽，存入 arr[mid]
		int const mid = (left + right) >> 1; // 真心累
		int const r1 = right - 1;
		int const r2 = right - 2;
		if (a[left] > a[mid]) swap(a + left, a + mid);
		if (a[left] > a[r1]) swap(a + left, a + r1);
		if (a[mid] > a[r1]) swap(a + mid, a + r1);
		swap(a + mid, a + r2);
		int const pivot = a[r2];
		int m = left; int n = r2;
		while (true)
		{
			//	while (a[++m] < pivot); // 1
			//	while (a[--n] > pivot);  // 1
			// 有等号需要判断边界
			while (m < n && a[m] <= pivot) ++m; // 2
			while (m < n && a[n] >= pivot) --n; // 2
			if (m < n) swap(a + m, a + n);
			else break;
		}
		// 放回枢纽
		a[r2] = a[m]; a[m] = pivot;
		quickSort(a, left, m);
		quickSort(a, m + 1, right);
	}
}

int main(int argc, char**)
{
	//	std::ios::sync_with_stdio(false);
	//	std::ostringstream oss;
	bool testSelect = true;
	if (argc > 1) testSelect = false;
	int rt = 0;
	int const k = 125;
	int const num = 200;
	int arr[num];
	srand((unsigned int)(time(NULL))); // 设置为常数或不设置以调试

	/* 随机化 */
	printf("\nRandom %d numbers:\n\n", num);
	//	oss << "\nRandom " << num << " numbers:\n\n";
	for (int m = 0; m < num; ++m)
	{
		int const n = rand();
		arr[m] = n;
		printf("%6d  ", n);
		// oss << std::setw(6) << n << "  ";
	}

	if (testSelect) /**< 选择 */
	{
		printf("\n\nLeast %d numbers:\n\n", k);
		// oss << "\n\nLeast " << k << " numbers:\n\n";
		quickSelect(arr, k, 0, num);

		// 输出
		int m = 0;
		for (m = 0; m < k; ++m)
			printf("%6d  ", arr[m]);
		// oss << std::setw(6) << arr[m] << "  ";
		//	oss << "\n\n";
		printf("\n\n");
		for (; m < num; ++m)
			printf("%6d  ", arr[m]);
		// oss << std::setw(6) << arr[m] << "  ";

		// 检查选择
		int fmax = arr[0];
		for (m = 1; m < k; ++m)
			if (fmax < arr[m])
				fmax = arr[m];
		for (; m < num; ++m)
			if (fmax > arr[m])
			{ rt = m;  break; } // 未通过
	}
	else /**< 排序 */
	{
		printf("\n\nAfter sorting:\n\n");
		//	oss << "\n\nAfter sorting:\n\n";
		quickSort(arr, 0, num);

		// 输出
		for (int m = 0; m < num; ++m)
			printf("%6d  ", arr[m]);
		// oss << std::setw(6) << arr[m] << "  ";

		// 检查排序
		for (int m = 1; m < num; ++m)
			if (arr[m - 1] > arr[m])
			{ rt = m; break; }
	}

	printf("\n");
	//	oss << "\n";
	//	std::cout << oss.str() << std::flush;
	return rt;
}
