// https://msdn.microsoft.com/zh-cn/library/dd470426.aspx

#include <Windows.h>

#include <ppl.h>
#include <concurrent_vector.h>
#include <concurrent_queue.h>
using namespace Concurrency;

#include <vector>
#include <bitset>
#include <random>
#include <array>
#include <numeric>
#include <iostream>
#include <sstream>
using std::wcout; using std::endl;


/** 统计函数执行时间 */
template<class Func, class... Args>
unsigned timeCall(Func&& func, Args&&... args)
{
	DWORD begin = GetTickCount();
	func(std::forward<Args>(args)...);
	return static_cast<unsigned>(GetTickCount() - begin);
}


/** 判断一个数是不是质数 */
bool isPrime(unsigned n)
{
	if (n == 2u) return true;
	if (n < 2u) return false;
	if (!(n & 1u)) return false;
	for (unsigned u = 3u; u < n; u += 2u)
	{
		if (!(n % u))
			return false;
	}
	return true;
}


/** 计算范围内所有质数的和 */
void sumPrime()
{
	std::array<unsigned, 100000> arr;
	std::iota(arr.begin(), arr.end(), 0u);

	unsigned sum;
	unsigned elapsed;

	// 使用串行操作
	elapsed = timeCall([&sum, &arr]() -> void
	{
		std::transform(arr.begin(), arr.end(), arr.begin(), \
			[](unsigned u) -> unsigned { return isPrime(u) ? u : 0u; });
		sum = std::accumulate(arr.begin(), arr.end(), 0u);
	});
	wcout << sum << L"\nserial time: " << elapsed << L"ms" << endl;

	// 使用并行操作
	elapsed = timeCall([&sum, &arr]() -> void
	{
		parallel_transform(arr.begin(), arr.end(), arr.begin(), \
			[](unsigned u) -> unsigned { return isPrime(u) ? u : 0u; });
		sum = parallel_reduce(arr.begin(), arr.end(), 0u);
	});
	wcout << sum << L"\nparallel time: " << elapsed << L"ms" << endl;
	
	wcout << L"----- function: " __FUNCTIONW__ L"\n" << endl;
}


struct Point { int x, y, z; };

unsigned distL2(Point const& A, Point const& B)
{
	int y = A.y - B.y;
	int x = A.x - B.x;
	int z = A.z - B.z;
	unsigned dist = static_cast<unsigned>(sqrt(x * x + y * y + z * z));
	return dist;
}

/** 此示例演示如何为 parallel_radixsort 算法提供哈希函数
 * 此示例对三维点排序，根据这些点与参考点的距离对它们进行排序 */
void sortPoint()
{
	// 参考点
	Point const center = { 3, 2, 7 };

	// 创建几个随机点
	std::vector<Point> pts(7);
	std::mt19937 gen(42);
	std::generate(pts.begin(), pts.end(), [&gen]() -> Point
	{
		Point p = { gen() % 10u, gen() % 10u, gen() % 10u };
		return p;
	});

	// 输出点
	wcout << L"before sort:";
	std::for_each(pts.begin(), pts.end(), [center](Point const& p) -> void
	{
		wcout << L"\n(" << p.x << L", " << p.y << L", " << p.z << \
			L"); d = " << distL2(center, p);
	});
	wcout << "\n";

	// 根据距离排序
	parallel_radixsort(pts.begin(), pts.end(), \
		[center](Point const& p) -> unsigned { return distL2(center, p); });

	// 输出结果
	wcout << L"after sort:";
	std::for_each(pts.begin(), pts.end(), [center](Point const& p) -> void
	{
		wcout << L"\n(" << p.x << L", " << p.y << L", " << p.z << \
			L"); d = " << distL2(center, p);
	});
	wcout << "\n";

	wcout << L"----- function: " __FUNCTIONW__ L"\n" << endl;
}


// 必须是全变量，因为捕获后就不是常量表达式
unsigned const limit = 40000u;
/** 计算质数集 */
void setPrime()
{
	using std::bitset;
	bitset<limit> set1, set2;
	unsigned elapsed;

	// 串行
	elapsed = timeCall([&set1]() -> void
	{
		for (unsigned u = 0; u < limit; u++)
			if (isPrime(u))
				set1.set(u);
	});
	wcout << L"serial time: " << elapsed << L" ms\n";

	// 并行
	elapsed = timeCall([&set2]() -> void
	{
		// 使用 parallel_for 和 combinable 对象
		// 不需要同步访问，因为 combinable 对象可以给每个线程复制一个 bitset
		combinable<bitset<limit>> cbset;
		parallel_for(0u, limit, [&cbset](unsigned u) -> void
		{
			if (isPrime(u))
				cbset.local().set(u);
		});

		// 合并各线程的结果
		cbset.combine_each([&set2](bitset<limit>& cb) -> void { set2 |= cb; });
	});
	wcout << L"parallel time: " << elapsed << L" ms\n";

	wcout << L"----- function: " __FUNCTIONW__ L"\n" << endl;
}


/** 判断一个数是不是卡迈尔数
 * 合数 n 是卡迈尔数，当且仅当对于它的所有质因子 b，有
 * (1) n 是 square-free 的，即所有质因子都不同 (b^2 不能整除 n)
 * (2) (b - 1) 能整除 (n - 1) */
bool isCarmichael(unsigned const n)
{
	if (n < 2u) return false;

	unsigned k = n;
	for (unsigned u = 2u; u <= k / u; ++u)
	{
		if ((k % u) == 0u)
		{
			if ((k / u) % u == 0u)
				return false;
			if ((n - 1u) % (u - 1u))
				return false;
			k /= u;
			u = 1u;
		}
	}

	return (k != n) && ((n - 1u) % (k - 1u) == 0);
}


/** 使用试除法来查找给定值的所有质数因子 */
concurrent_vector<unsigned> primeFactor(unsigned n, \
	concurrent_vector<unsigned> const& primes)
{
	concurrent_vector<unsigned> factors;

	unsigned const sqrt_n = static_cast<unsigned>(sqrt(static_cast<double>(n)));
	parallel_for_each(primes.begin(), primes.end(), \
		[&factors, sqrt_n, n](unsigned b) -> void
	{
		if ((b <= sqrt_n) && ((n % b) == 0))
			factors.push_back(b);
	});

	return factors;
}


/* 输出每个具有 4 个以上的质数因子的卡迈尔数和它的质数因子
 * 通过调用 primeFactors 计算卡迈尔数的质数因子来处理队列中的每个元素
 * 使用任务组以并行方式执行此任务 */
void outCarmicheal()
{
	unsigned begin = GetTickCount();
	unsigned const maxval = 10000000u;
	concurrent_queue<unsigned> carmichaels;
	concurrent_vector<unsigned> primes;

	// 得到卡迈尔数和质数集合
	// 事实上，得到质数集合后再判断卡迈尔数更高效
	parallel_invoke(
		[&carmichaels, maxval]() -> void
	{
		parallel_for(0u, maxval, [&carmichaels](unsigned u) -> void
		{ if (isCarmichael(u)) carmichaels.push(u); });
	},
		[&primes, maxval]() -> void
	{
		parallel_for(0u, \
			static_cast<unsigned>(sqrt(static_cast<double>(maxval))), \
			[&primes](unsigned u) -> void
		{ if (isPrime(u)) primes.push_back(u); });
	});

	// 这里排序，tasks 里面就不用排序了
	std::sort(primes.begin(), primes.end());
	//std::sort(carmichaels.unsafe_begin(), carmichaels.unsafe_end());
	
	// 使用任务组，计算每个卡迈尔数的所有质因子
	task_group tasks;
	
	unsigned carm;
	while (carmichaels.try_pop(carm))
	{
		tasks.run([carm, &primes]() -> void
		{
			concurrent_vector<unsigned> factors = primeFactor(carm, primes);

			// 简化起见，仅仅打印质因子个数不少于 4 的卡迈尔数
			if (primes.size() > 3u)
			{
				// 排序输出
				// std::sort(factors.begin(), factors.end());

				std::wstringstream wss;
				wss << L"prime factors of " << carm << " are: ";
				std::for_each(factors.begin(), factors.end(), \
					[&wss](unsigned b) -> void { wss << b << L", "; });
				wss << L"\b\b." << endl;
				wcout << wss.str();
			}
		});
	}

	// 等待任务结束
	tasks.wait();
	wcout << L"elapsed " << GetTickCount() - begin << L" ms\n";
	wcout << L"----- function: " __FUNCTIONW__ L"\n" << endl;
}



int wmain()
{
	sumPrime();
	sortPoint();
	setPrime();
	outCarmicheal();
}
