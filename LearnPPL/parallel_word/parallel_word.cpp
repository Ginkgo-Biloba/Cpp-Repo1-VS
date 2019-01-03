// https://msdn.microsoft.com/zh-cn/library/dd728072.aspx
/* 以下示例从 gutenberg.org 下载 Iliad by Homer 并对此文件执行多项操作。
 * 此示例首先按顺序执行这些操作，然后并行执行相同操作 */

#define _AFXDLL
#define _WIN32_WINNT 0x0501
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using std::wstring;
using std::pair;
using std::vector;
using std::wcout; using std::endl;
using std::for_each;

#include <afxinet.h>
#include <ppl.h>
#include <sysinfoapi.h>
using namespace Concurrency;


template<class Func>
uint32_t timeCall(Func&& func)
{
	uint32_t begin = GetTickCount();
	func();
	return GetTickCount() - begin;
}


// 下载文件
CString getHttpFile(CInternetSession& session, CString const& url);

// 添加给定的字符串中的每个单词到给定的字符串向量中
void makeWordList(wstring const& text, vector<wstring>& words);

// 寻找最常见的、长度大于等于给定的最小值的单词
vector<pair<wstring, size_t>> findCommonWords(vector<wstring> const& words, \
	size_t minLength, size_t count);

// 寻找最长的、具有相同首字母的单词序列
vector<wstring> findLongestSequence(vector<wstring> const& words);

// 寻找给定的单词中所有的回文组
vector<pair<wstring, wstring>> findPalindromes(vector<wstring> const& words, \
	size_t minLength);


int wmain()
{
	// 管理网络连接
	CInternetSession session(L"Microsoft Internet Browser");
	// 下载文件《伊利亚特》
	wcout << L"Downloading \"The Iliad\"...";
	wstring file = getHttpFile(session, L"http://www.gutenberg.org/files/6130/6130.txt").GetString();
	wcout << L" done" << endl;

	// 转化文本到一系列独立的单词
	vector<wstring> words;
	makeWordList(file, words);

	// 比较执行几个操作的时间
	uint32_t elapsed;

	vector<pair<wstring, size_t>> commonWords;
	vector<wstring> longestSequence;
	vector<pair<wstring, wstring>> palindromes;

	wcout << L"Running serial version: ";
	elapsed = timeCall([&commonWords, &longestSequence, &palindromes, &words]() -> void
	{
		commonWords = findCommonWords(words, 5, 9);
		longestSequence = findLongestSequence(words);
		palindromes = findPalindromes(words, 5);
	});
	wcout << L"took " << elapsed << L"ms" << endl;

	wcout << L"Running parallel version: ";
	elapsed = timeCall([&commonWords, &longestSequence, &palindromes, &words]() -> void
	{
		parallel_invoke(
			[&commonWords, &words]() -> void { commonWords = findCommonWords(words, 5, 9); },
			[&longestSequence, &words]() -> void { longestSequence = findLongestSequence(words); },
			[&palindromes, &words]() -> void { palindromes = findPalindromes(words, 5); }
		);
	});
	wcout << L"took " << elapsed << L"ms" << endl;
	wcout << endl;

	// 输出结果
	wcout << L"The most common words that have five or more letters are:" << endl;
	for_each(commonWords.begin(), commonWords.end(), \
		[](pair<wstring, size_t> const& p) -> void
	{ wcout << L"  " << p.first << L" (" << p.second << L") " << endl; });

	wcout << L"The longest sequence of words that have the same first letter is:" \
		<< endl << L"  ";
	for_each(longestSequence.begin(), longestSequence.end(), \
		[](wstring const& str) -> void { wcout << str << L" "; });
	wcout << endl;

	wcout << L"The following palindromes appear in the text:" << endl;
	for_each(palindromes.begin(), palindromes.end(), \
		[](pair<wstring, wstring> const& p) -> void \
	{wcout << L"  " << p.first << L"  " << p.second << endl; });
}


CString getHttpFile(CInternetSession& session, CString const& url)
{
	CString result;
	CHttpFile* http = nullptr;

	try
	{
		// 打开 URL
		http = reinterpret_cast<CHttpFile*>(session.OpenURL(url, 1));
		// 读取文件
		if (http) // != nullptr
		{
			UINT bytes;
			char buffer[10000];
			do
			{
				bytes = http->Read(buffer, sizeof(buffer));
				result += buffer;
			} while (bytes); // > 0
		}
	}
	catch (CInternetException&)
	{
		wcout << "HTTP Exception" << endl;
	}

	delete http;
	return result;
}


void makeWordList(wstring const& text, vector<wstring>& words)
{
	wstring curWord;

	for_each(text.begin(), text.end(), [&curWord, &words](wchar_t wch) -> void
	{
		if (!iswalnum(wch))
		{
			if (!curWord.empty())
			{
				words.push_back(curWord);
				curWord.clear();
			}
		}
		else
			curWord.push_back(wch);
	});
}


vector<pair<wstring, size_t>> findCommonWords(vector<wstring> const& words, \
	size_t minLength, size_t count)
{
	typedef std::pair<wstring, size_t> PWSz;
	typedef std::map<wstring, size_t> MWSz;
	MWSz wordcnt; // 统计每个单词出现的次数

	for_each(words.begin(), words.end(), \
		[&wordcnt, minLength, count](wstring const& ws) -> void
	{
		if (ws.length() >= minLength)
		{
			MWSz::iterator iter = wordcnt.find(ws);
			if (iter != wordcnt.end())
				++(iter->second);
			else
				wordcnt.emplace(ws, 1);
		}
	});


	// 复制 map 的内容到 vector，并根据出现次数排序
	vector<PWSz> wordvec;
	std::copy(wordcnt.begin(), wordcnt.end(), std::back_inserter(wordvec));
	std::sort(wordvec.begin(), wordvec.end(), \
		[](PWSz const& x, PWSz const& y) -> bool { return x.second > y.second; });

	size_t size = std::min<size_t>(wordvec.size(), count);
	wordvec.erase(wordvec.begin() + size, wordvec.end());

	return wordvec;
}


vector<wstring> findLongestSequence(vector<wstring> const& words)
{
	// 当前具有相同首字母的单词序列
	vector<wstring> cand;
	// 最长的具有相同首字母的单词序列
	vector<wstring> longest;

	for_each(words.begin(), words.end(), \
		[&cand, &longest](wstring const& ws) -> void
	{
		// 如果为空，初始化
		if (cand.empty())
			cand.push_back(ws);
		// 添加单词到候选序列，如果单词与序列中每个单词的首字母都相同
		else if (ws[0] == cand[0][0])
			cand.push_back(ws);
		// 首字母改变了，重置列表
		else
		{
			if (cand.size() > longest.size())
				longest.swap(cand);

			cand.clear();
			cand.push_back(ws);
		}
	});

	if (cand.size() > longest.size())
		longest.swap(cand);
	return longest;
}


vector<pair<wstring, wstring>> findPalindromes(vector<wstring> const& words, \
	size_t minLength)
{
	typedef std::pair<wstring, wstring> PWW;
	vector<PWW> result;

	// 复制单词到新的 vector 中，并排序
	vector<wstring> wordvec;
	std::copy(words.begin(), words.end(), std::back_inserter(wordvec));
	std::sort(wordvec.begin(), wordvec.end());
	// wordvec.erase(std::unique(wordvec.begin(), wordvec.end()), wordvec.end());

	// 添加一个单词，如果它的回文也存在
	for_each(words.begin(), words.end(), \
		[&result, &wordvec, minLength](wstring const& ws) -> void
	{
		if (ws.length() < minLength)
			return;
		wstring rev = ws;
		std::reverse(rev.begin(), rev.end());
		if (std::binary_search(wordvec.begin(), wordvec.end(), rev))
		{
			PWW cand(ws, rev);
			if (rev < ws) // 小的在前
				cand.first.swap(cand.second);

			if (std::find(result.begin(), result.end(), cand) == result.end())
				result.push_back(std::move(cand));
		}
	});

	return result;
}


