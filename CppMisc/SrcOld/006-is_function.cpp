#include <cstdio>
#include <type_traits>

/** ����˼���ǣ������Ԫ�ز����� void�����û��ߺ��� */
template<class Tp>
class IsFunction
{
private: // private ���ԣ���Ϊֻ�Ǳ������жϣ�����ʵ����ֵ
	typedef char(&one)[1];
	typedef char(&two)[2];

	template<class C>
	static one test(...);
	template<class C>
	static two test(C(*)[1]);

public:
	static int const value =
		sizeof(test<Tp>(0)) == sizeof(one);
};

/** �ػ��������� */
template<class Tp>
class IsFunction<Tp&>
{
public:
	static int const value = 0;
};

/** �ػ� void ���� */
template<>
class IsFunction<void>
{
public:
	static int const value = 0;
};


class Dummy
{
public:
	typedef void func(char);
};
int p();

int main()
{
#define out(x) printf(#x " = %d\n", (int)(x))
	typedef char(&one)[1];
	typedef char(&two)[2];
	out(sizeof(one));
	out(sizeof(two));
	out(sizeof(char(&)[1]));
	out(sizeof(char(&)[2]));
	out(IsFunction<int>::value);
	out(IsFunction<int*>::value);
	out(IsFunction<int&>::value);
	out(IsFunction<void>::value);
	out(IsFunction<int(char)>::value);
	out(IsFunction<Dummy::func>::value);
	out(std::is_function<Dummy::func>::value);
	printf("***** End of main *****\n");
#undef out
}