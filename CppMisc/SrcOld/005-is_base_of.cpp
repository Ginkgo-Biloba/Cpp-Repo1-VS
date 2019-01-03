#include <cstdio>
#include <cstdlib>
#include <type_traits>

typedef char(&yes)[1];
typedef char(&no)[2];

// Not same
template<typename B, typename D>
struct is_same { static bool const value = false; };
// Same
template <typename B>
struct is_same<B, B> { static bool const value = true; };

// Is class or not
template <typename B>
struct is_class
{
	template<typename T>
	static yes check(int T::*); // char, short, float, double is well too
	template<typename T>
	static no check(...);

	static bool const value = (sizeof(check<B>(0)) == sizeof(yes));
};

// Convert
template <typename B, typename D>
struct Conv
{
	operator D*();
	operator B*() const;
};

// Both are classes
template <typename B, typename D, \
	bool = (::is_class<B>::value && ::is_class<D>::value)>
struct is_base_of
{
	template <typename T>
	static yes check(D*, T);
	static no check(B*, int);

	static bool const value = \
		(::is_same<B, D>::value || sizeof(check(Conv<B, D>(), 0)) == sizeof(yes));
};

// Not both are classes
template<typename B, typename D>
struct is_base_of<B, D, false> { static bool const value = false; };

// Test sample, depth-2
class Base {};
class Middle : private Base {};
class Derived : private Middle {};

// Expression is true
int test[::is_base_of<Base, Derived>::value && !::is_base_of<Derived, Base>::value];

int main()
{
	fprintf(stdout, "\nis_same ==========\n");
	fprintf(stdout, "%6s || <B, B> : %d | <B, D> : %d\n", "global", \
		::is_same<Base, Base>::value, ::is_same<Base, Derived>::value);
	fprintf(stdout, "%6s || <B, B> : %d | <B, D> : %d\n", "std", \
		std::is_same<Base, Base>::value, std::is_same<Base, Derived>::value);

	fprintf(stdout, "\nis_class ==========\n");
	fprintf(stdout, "%6s || <B> : %d | <float> : %d\n", "global", \
		::is_class<Base>::value, ::is_class<float>::value);
	fprintf(stdout, "%6s || <B> : %d | <float> : %d\n", "std", \
		std::is_class<Base>::value, std::is_class<float>::value);

	fprintf(stdout, "\nsizeof ==========\n");
	fprintf(stdout, "sizeof yes: %zd | sizeof no: %zd\n", sizeof(yes), sizeof(no));
	fprintf(stdout, "sizeof test: %zd\n", sizeof(test));

	fprintf(stdout, "\nis_base_of ==========\n");
	fprintf(stdout, "%6s || <B, D>: %d | <B, B>: %d | <void, B>: %d | <float, float>: %d\n", "global", \
		::is_base_of<Base, Derived>::value, ::is_base_of<Base, Base>::value, \
		::is_base_of<void, Base>::value, ::is_base_of<float, float>::value);
	fprintf(stdout, "%6s || <B, D>: %d | <B, B>: %d | <void, B>: %d | <float, float>: %d\n", "std", \
		std::is_base_of<Base, Derived>::value, std::is_base_of<Base, Base>::value, \
		std::is_base_of<void, Base>::value, std::is_base_of<float, float>::value);
}

