#include "../src/utility.hpp"


void merge(vector<int>& A, int lenA, vector<int>& B, int lenB)
{
	int idxEnd = lenA + lenB - 1;
	if (lenA == 0) A.swap(B);
	if (lenA == 0 || lenB == 0) return;
	--lenA; --lenB;

	while (lenA >= 0 && lenB >= 0)
	{
		if (A[lenA] >= B[lenB])
		{
			A[idxEnd] = A[lenA];
			--lenA;
		}
		else
		{
			A[idxEnd] = B[lenB];
			--lenB;
		}
		--idxEnd;
	}
	for (; lenB >= 0; --lenB)
		A[lenB] = B[lenB];
}

int main()
{
	vector<int> A = { 1, 2, 3, 0, 0, 0 }, B = {2, 5, 6};
	merge(A, 3, B, static_cast<int>(B.size()));
	output(A, "merge");
}
