#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>
#include <memory>


namespace details
{
template<class Tp>
struct WarpFree
{
	void operator()(Tp* ptr) const
	{ free(ptr); }
};
}

/** 管理 POD 类型，不初始化 */
template<class Tp>
std::shared_ptr<Tp> makeArrayPOD(size_t count)
{
	static_assert(std::is_pod<Tp>::value, "POD type required");
	return std::shared_ptr<Tp>(
		static_cast<Tp*>(malloc(count * sizeof(Tp))),
		details::WarpFree<Tp>());
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	int count = 10;
	std::shared_ptr<int> p = makeArrayPOD<int>(count);
	p.get()[1] = 1;
	while (count--)
		printf("%2d: %d\n", count, p.get()[count]);
}

