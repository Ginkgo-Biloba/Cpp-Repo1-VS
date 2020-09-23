#include "leetcode.hpp"

/* 1171. 从链表中删去总和值为零的连续节点

给你一个链表的头节点 head，请你编写代码，反复删去链表中由 总和 值为 0 的连续节点组成的序列，直到不存在这样的序列为止。

删除完毕后，请你返回最终结果链表的头节点。

你可以返回任何满足题目要求的答案。

注意，下面示例中的所有序列，都是对 ListNode 对象序列化的表示。

示例 1：
输入：head = [1,2,-3,3,1]
输出：[3,1]
提示：答案 [1,2,1] 也是正确的。

示例 2：
输入：head = [1,2,3,-3,4]
输出：[1,2,4]

示例 3：
输入：head = [1,2,3,-3,-2]
输出：[1]

提示：
	给你的链表中可能有 1 到 1000 个节点。
	对于链表中的每个节点，节点的值：-1000 <= node.val <= 1000.
*/


// Definition for singly-linked list.
struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x)
		: val(x)
		, next(NULL)
	{}
};

// https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/discuss/366350/C%2B%2B-O(n)-(explained-with-pictures)
// 抄的
class Solution
{
public:
	ListNode* removeZeroSumSublists(ListNode* head)
	{
		unordered_map<int, ListNode*> M;
		ListNode root = ListNode(0);
		int sum = 0;
		root.next = head;
		M[0] = &root;

		while (head)
		{
			sum += head->val;
			if (M.find(sum) != M.end())
			{
				ListNode *prev = M[sum], *start = prev;
				int aux = sum;
				while (prev != head)
				{
					prev = prev->next;
					aux += prev->val;
					if (prev != head)
						M.erase(aux);
				}

				start->next = head->next;
			}
			else
				M.emplace(sum, head);
			head = head->next;
		}
		return root.next;
	}
};


int main()
{}
