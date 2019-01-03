#include <intrin.h>
#include <cstdio>
#include <ppl.h>
using Concurrency::critical_section;
using Concurrency::parallel_invoke;

class Inc
{
	long& i; int c; critical_section& cs;

public:
	Inc(long& var, int count, critical_section& csec)
		: i(var), c(count), cs(csec)
	{}

	void operator()() const
	{
		int cc = c;
		while (cc--)
		{
			// cs.lock(); i += 1l; cs.unlock();
			// i += 1l;
			_InterlockedExchangeAdd(&i, 1l);
		}
	}
};


int main()
{
	long i = 0; int c = 10000000; critical_section cs;
	clock_t start = clock();
	_mm_mfence();
	parallel_invoke(Inc(i, c, cs), Inc(i, c, cs), Inc(i, c, cs));
	_mm_mfence();
	clock_t stop = clock();
	printf("i = %ld, clock = %ld\n", i, (long)(stop - start));
}







