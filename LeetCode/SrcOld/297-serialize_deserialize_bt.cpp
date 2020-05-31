#include "leetcode.hpp"

/* 297. 二叉树的序列化与反序列化

序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

请设计一个算法来实现二叉树的序列化与反序列化。
这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

示例:

你可以将以下二叉树：

>    1
>   / \
>  2   3
>     / \
>    4   5

序列化为 "[1,2,3,null,null,4,5]"

提示: 这与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。
你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。

说明: 不要使用类的成员 / 全局 / 静态变量来存储状态，你的序列化和反序列化算法应该是无状态的。
*/

// Definition for a binary tree node.
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x)
		: val(x)
		, left(NULL)
		, right(NULL)
	{}
};

class Codec
{
	TreeNode* extract(string& s, size_t& i)
	{
		TreeNode* node = NULL;
		if (s[i] == '~')
		{
			// 跳过 ~ 和 ,
			i += 2;
			return NULL;
		}
		char* ptr = NULL;
		long val = strtol(s.c_str() + i, &ptr, 10);
		node = new TreeNode(val);
		// 跳过 ,
		i = ptr - s.c_str() + 1;
		return node;
	}

public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root)
	{
		char buf[32];
		string ans;
		if (!root)
			return ans;
		vector<TreeNode*> curr, temp;
		curr.push_back(root);
		while (curr.size())
		{
			temp.clear();
			string s;
			for (TreeNode* node : curr)
			{
				if (!node)
				{
					s.append("~,");
					continue;
				}
				sprintf(buf, "%d,", node->val);
				s.append(buf);
				temp.push_back(node->left);
				temp.push_back(node->right);
			}
			if (temp.size())
				ans += s;
			temp.swap(curr);
		}
		return ans;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data)
	{
		if (data.empty())
			return NULL;
		size_t i = 0;
		TreeNode* root = extract(data, i);
		vector<TreeNode*> curr, temp;
		curr.push_back(root);
		while (i < data.size())
		{
			temp.clear();
			for (TreeNode* node : curr)
			{
				node->left = extract(data, i);
				node->right = extract(data, i);
				if (node->left)
					temp.push_back(node->left);
				if (node->right)
					temp.push_back(node->right);
			}
			temp.swap(curr);
		}
		return root;
	}
};


int main()
{
	Codec c;
	TreeNode r(1);
	r.left = new TreeNode(2);
	r.right = new TreeNode(-3);
	r.right->left = new TreeNode(4);
	r.right->right = new TreeNode(5);
	string s = c.serialize(&r);
	TreeNode* d = c.deserialize(s);
	return d->val == r.val;
}
