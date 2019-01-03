#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <cfloat>

float funcR(float const* ptr, int num, int* a, int* b)
{
	float sum = 0.f;
	for (int n = 0; n < num; ++n)
	{
		float x = ptr[n];
		float const dx1 = std::copysign(0.5f - FLT_EPSILON, x);
		int x1 = static_cast<int>(x + dx1 + 0.5f) & ~1;
		float const dx2 = (x > 0.f) ? std::ceil(x) : x;
		int x2 = static_cast<int>(dx2) & ~1;
		
		a[n] = x1; b[n] = x2;
		x = static_cast<float>(x1 - x2);
		sum += x * x;
	}
	return sum;
}


int main()
{
	int const num = 100;
	float x[num];
	int a[num], b[num];
	for (int n = 0; n < num; ++n)
		x[n] = (n - 50) * 0.1f;
	float sum = funcR(x, num, a, b);
	printf("sum = %f\n", sum);
	for (int n = 0; n < num; ++n)
		printf("%2d: %5.1f, %2d, %2d\n", n, x[n], a[n], b[n]);
}


