#include "../srcOld/utility.hpp"

class Solution
{
protected:
	struct TrieNode
	{
		static size_t const numChar = 26;
		TrieNode* next[numChar];
		string word;

		TrieNode() { memset(next, 0, sizeof(next)); }
	};


	TrieNode* buildTrie(vector<string> const& words)
	{
		TrieNode* root = new TrieNode();
		for (string const& str : words)
		{
			TrieNode* head = root;
			for (char c : str)
			{
				c -= 'a';
				if (!(head->next[c]))
					head->next[c] = new TrieNode();
				head = head->next[c];
			}
			head->word = str;
		}
		return root;
	}


	void clearTrie(TrieNode* root)
	{
		if (root == nullptr) return;

		vector<TrieNode*> ready;
		ready.push_back(root);
		size_t finish = 0;

		while (finish < ready.size())
		{
			TrieNode* cur = ready[finish]; ++finish;
			for (size_t i = 0; i < TrieNode::numChar; ++i)
			{
				if (cur->next[i])
					ready.push_back(cur->next[i]);
			}
			delete cur;
		}
	}


	void dfs(vector<vector<char>>& board, size_t r, size_t c, \
		TrieNode* p, vector<string>& ans)
	{
		char ch = board[r][c];
		if (ch == '#' || !(p->next[ch - 'a'])) return;

		p = p->next[ch - 'a'];
		if (!(p->word.empty()))
		{
			ans.push_back(p->word);
			p->word.clear(); // 删除，不用考虑 words 有重复的情况
		}

		board[r][c] = '#'; // 直接修改，不用标记是否访问过，省内存加速
		if (r > 0) dfs(board, r - 1u, c, p, ans);
		if (c > 0) dfs(board, r, c - 1u, p, ans);
		if (r + 1u < board.size()) dfs(board, r + 1u, c, p, ans);
		if (c + 1u < board[0].size()) dfs(board, r, c + 1u, p, ans);
		board[r][c] = ch; // 恢复现场
	}

public:
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
	{
		vector<string> ans;

		size_t rows = board.size();
		if (!rows) return ans;

		size_t cols = board[0].size();
		TrieNode* root = buildTrie(words);
		for (size_t r = 0; r < rows; ++r)
		{
			for (size_t c = 0; c < cols; ++c)
				dfs(board, r, c, root, ans);
		}
		clearTrie(root);

		return ans;
	}

};


int main()
{
	vector<string> words = { "oath", "pea", "eat", "rain" };
	vector<vector<char>> board =
	{
		{ 'o', 'a', 'a', 'n' },
		{ 'e', 't', 'a', 'e' },
		{ 'i', 'h', 'k', 'r' },
		{ 'i', 'f', 'l', 'v' }
	};
	vector<string> exist = Solution().findWords(board, words);
	output(exist, ", ", "findWords");
}
