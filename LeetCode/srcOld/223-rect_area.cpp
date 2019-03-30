#include "utility.hpp"


int computeArea(int A, int B, int C, int D, int E, int F, int G, int H)
{
	int area = (C - A) * (D - B);
	int overlap = 0;
	int left = std::max(A, E), right = std::min(C, G);
	int bottom = std::max(B, F), top = std::min(D, H);
	if ((left < right) && (bottom < top))
		overlap = (right - left) * (top - bottom);

	area += (G - E) * (H - F) - overlap;
	return area;
}


int main()
{
	int ans = computeArea(-3, 0, 3, 4, 0, -1, 9, 2);
	printf("%1s = %d\n", "Rectangle Area", ans);
}
