#include <cstdio>
#include <cstdlib>

int maxArray(int const* array, int start, int stop)
{
	if (stop - start == 1) return array[start];

	int iM = (stop - start + 1) / 2 + start;
	int L = maxArray(array, start, iM);
	int R = maxArray(array, iM, stop);

	int cur = 0;
	int mL = 0, mR = array[iM];
	for (int iL = iM - 1; iL >= start; iL--)
	{
		cur += array[iL];
		if (cur > mL) mL = cur;
	}
	cur = mR;
	for (int iR = iM + 1; iR < stop; iR++)
	{
		cur += array[iR];
		if (cur > mR) mR = cur;
	}

	int M = mL + mR;

	if (L > R)
		return (M > L) ? M : L;
	else
		return (M > R) ? M : R;
}



int maxSubArray(int const* array, int num)
{
	return maxArray(array, 0, num);
}


int main()
{
	int const array[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	printf("%d\n", maxSubArray(array, sizeof(array) / sizeof(int)));
}
