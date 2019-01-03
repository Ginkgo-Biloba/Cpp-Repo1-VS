#include <string>
#include <vector>
#include <iostream>
typedef std::vector<std::string> rsttype;

void dfs(rsttype& ans, std::string& local, int left, int right, int n)
{
	if (left < right || right > n || left > n) return;
	if (left == right && left == n) ans.push_back(local);
	else
	{
		/* 好像并省不了多少内存…… */
		local.push_back('(');
		dfs(ans, local, left + 1, right, n);
		local.back() = ')';
		dfs(ans, local, left, right + 1, n);
		local.pop_back();
	}
}

rsttype genPth(int n)
{
	if (n > 15) n = 15; /* 15 -> 9694845 不小了 */
	rsttype ans;
	std::string local;
	dfs(ans, local, 0, 0, n);
	return ans;
}

int main()
{
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	rsttype ans = genPth(n);
	std::cout << "Count("  << n << "): " << ans.size() << "\n";
	for (std::string const& s : ans)
		std::cout << s << "\n";
	return 0;
}