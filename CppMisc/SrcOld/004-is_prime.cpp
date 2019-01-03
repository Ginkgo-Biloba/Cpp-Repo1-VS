
template<int p, int i>
struct is_prime
{
	enum { prime = (p == 2) || ((p % i) && is_prime<(i > 2 ? p : 0), i - 1>::prime) };
};


template<>
struct is_prime<0, 0>
{
	enum { prime = 1 };
};

template<>
struct is_prime<0, 1>
{
	enum { prime = 1 };
};


template<int i>
struct D
{
	D(void*); // 不需要定义
};


// 用于循环输出质数的基本模板
template<int i>
struct prime_print
{
	prime_print<i - 1> next;
	enum { prime = is_prime<i, i - 1>::prime };
	void func()
	{
		D<i> d = prime ? 1 : 0;
		next.func();
	}
};

// 用于结束递归的全局特化
template<>
struct prime_print<1>
{
	enum { prime = 0 };
	void func()
	{
		D<1> d = prime ? 1 : 0;
	}
};


int main()
{
	prime_print<18> p;
	p.func();
}

