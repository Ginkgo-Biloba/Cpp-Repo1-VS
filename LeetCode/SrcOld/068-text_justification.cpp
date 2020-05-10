#include "leetcode.hpp"

/* 68. 文本左右对齐

给定一个单词数组和一个长度 maxWidth，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。

你应该使用“贪心算法”来放置给定的单词；也就是说，尽可能多地往每行中放置单词。
必要时可用空格 ' ' 填充，使得每行恰好有 maxWidth 个字符。

要求尽可能均匀分配单词间的空格数量。
如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。

文本的最后一行应为左对齐，且单词之间不插入额外的空格。

说明:
	单词是指由非空格字符组成的字符序列。
	每个单词的长度大于 0，小于等于 maxWidth。
	输入单词数组 words 至少包含一个单词。

示例:

输入:
words = ["This", "is", "an", "example", "of", "text", "justification."]
maxWidth = 16
输出:
[
	"This    is    an",
	"example  of text",
	"justification.  "
]

示例 2:

输入:
words = ["What","must","be","acknowledgment","shall","be"]
maxWidth = 16
输出:
[
	"What   must   be",
	"acknowledgment  ",
	"shall be        "
]
解释:
注意最后一行的格式应为 "shall be    " 而不是 "shall     be",
因为最后一行应为左对齐，而不是左右两端对齐。
第二行同样为左对齐，这是因为这行只包含一个单词。

示例 3:

输入:
words =[
	"Science","is","what","we","understand","well","enough","to","explain",
	"to","a","computer.","Art","is","everything","else","we","do"]
maxWidth = 20
输出:
[
	"Science  is  what we",
	"understand      well",
	"enough to explain to",
	"a  computer.  Art is",
	"everything  else  we",
	"do                  "
]
*/

vector<string> fullJustify(vector<string>& words, int maxWidth)
{
	int len = static_cast<int>(words.size());
	int i = 0, k, w, t, d, s;
	vector<string> R;
	string r, b;
	b.reserve(maxWidth / 2);
	while (i < len)
	{
		w = static_cast<int>(words[i].length());
		for (k = i + 1; k < len; ++k)
		{
			t = static_cast<int>(words[k].length());
			if (w + t + (k - i) > maxWidth)
				break;
			w += t;
		}
		d = k - i - 1; // 间隔数量
		s = maxWidth - w; // 空格数量
		if (d != 0)
		{
			if (k != len)
			{
				w = s / d; // 平均每个间隔多少空格
				t = s - d * w; // 前 t 个多一个空格
				b.assign(w + 1, ' ');
				for (; i < k; ++i, --t)
				{
					if (t == 0)
						b.pop_back();
					r += words[i];
					if (i != k - 1)
						r += b;
				}
			}
			else
			{
				// 最后一行则单词间隔只有一个空格
				for (; i < k; ++i)
				{
					r += words[i];
					if (i + 1 != k)
						r.push_back(' ');
				}
				t = maxWidth - static_cast<int>(r.length());
				for (; t > 0; --t)
					r.push_back(' ');
			}
		}
		else
		{
			// 一个单词，空格填到尾部
			r.swap(words[i]);
			for (; s > 0; --s)
				r.push_back(' ');
			i = k;
		}
		R.push_back(move(r));
	}
	return R;
}


int main()
{
	vector<string>
		a = { "This", "is", "an", "example", "of", "text", "justification." },
		b = { "What", "must", "be", "acknowledgment", "shall", "be" },
		c = { "Science", "is", "what", "we", "understand", "well", "enough", "to", "explain", "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do" };
	output(fullJustify(a, 16), "|\n", "Text Justification");
	output(fullJustify(b, 16), "|\n", "Text Justification");
	output(fullJustify(c, 20), "|\n", "Text Justification");
}
