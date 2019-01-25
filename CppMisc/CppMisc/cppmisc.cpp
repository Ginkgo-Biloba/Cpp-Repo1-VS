#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <emmintrin.h>


int main()
{
	float fs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	float vs[4], ws[4];
	__m128 i0, i1, v, w;
	i0 = _mm_loadu_ps(fs);
	i1 = _mm_loadu_ps(fs + 4);
	v = _mm_shuffle_ps(i0, i1, 0b10001000);
	w = _mm_shuffle_ps(i0, i1, 0b11011101);
	_mm_storeu_ps(vs, v);
	_mm_storeu_ps(ws, w);
	_mm_clflush(fs);
}

