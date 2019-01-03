#include <cstdio>
#include <cstdlib>
#include <ctime>

// http://www.hawstein.com/posts/add-singly-linked-list.html
/* 求两个单链表的和
两个单链表 (singly linked list)，每一个节点里面一个0-9的数字， 输入就相当于两个大数了。
然后返回这两个数的和（一个新 list）。这两个输入的 list 长度相等。 要求是：
1. 不用递归。
2. 要求算法在最好的情况下，只遍历两个list一次， 最差的情况下两遍。*/

struct Node
{
	char data; // 保存 0 - 9 或两个数的和，1 字节即可
	Node* next;
};

// 将数组转换成链表
Node* mkList(char const* arr, int const& n)
{
	if (n < 1) return nullptr;
	Node* head = new Node();
	head->data = arr[0];
	Node* prev = head;
	Node* curr = nullptr;
	for (int k = 1; k < n; ++k)
	{
		curr = new Node();
		curr->data = arr[k];
		prev->next = curr;
		prev = curr;
	}
	curr->next = nullptr;
	return head;
}

// 清理链表空间
void delList(Node* head)
{
	while (head != nullptr)
	{
		Node* p = head->next;
		delete head;
		head = p;
	}
}

Node* listSum1(Node* pa, Node* pb, int& carry)
{
	if (pa == nullptr || pb == nullptr) return nullptr;
	Node* pc = new Node();
	Node* p = nullptr; Node* q = nullptr; // p 为 q 往前第一个不为 9 的节点
	Node* m = nullptr; // q 的前一节点
	char hs = pa->data + pb->data;
	if (hs >= 9) // 多开一个节点保存进位
	{
		m = new Node(); pc->next = m;
		carry = hs % 10; m->data = (char)(carry);
		if (hs > 9) // 和大于 9，最高位置 1，p 指向第二位 (待进位)
		{ pc->data = 1; p = m; }
		else // 和为 9，p 指向第一位，因为后面可能进位
		{ pc->data = 0; p = pc; }
	}
	else // 和小于 9
	{
		pc->data = hs;
		p = pc; m = pc;
		carry = 0;
	}
	pa = pa->next; pb = pb->next;
	// 后面的节点
	while ((pa != nullptr) && (pb != nullptr))
	{
		q = new Node();
		m->next = q;
		char s = pa->data + pb->data;
		if (s > 9) // 处理进位
		{
			p->data += 1; // 进位
			for (p = p->next; p != q; p = p->next) // p、q 间节点置零
				p->data = 0;
			q->data = s - 10;
		}
		else if (s < 9) // 后移 p 到 q
		{ q->data = s; p = q; }
		// 等于 9 不用管
		m = q; //更新前一节点
		pa = pa->next; pb = pb->next;
	}
	q->next = nullptr; // 尾节点置空
	if (pa != nullptr) printf("\nList 1 is too long");
	if (pb != nullptr) printf("\nList 2 is too long");
	// 如果最高位是 9 但是没有进位，删除 0
	if (hs == 9 && pc->data == 0)
	{
		p = pc->next;
		delete pc; pc = p;
		carry = 0;
	}
	return pc;
}

// 与上一个相同，只有进位那儿代码少一些
Node* listSum2(Node* pa, Node* pb, int& carry)
{
	if (pa == nullptr || pb == nullptr) return nullptr;
	Node* p = nullptr; Node* q = nullptr; // p 为 q 往前第一个不为 9 的节点
	Node* m = nullptr; // q 的前一节点
	/* 先不考虑进位问题，留着。前提是 char 能存下 18 */
	char hs = pa->data + pb->data;
	Node* pc = new Node();
	pc->data = hs;
	p = m = pc; carry = 0;
	// 处理后面的节点
	// 后面的节点
	pa = pa->next; pb = pb->next;
	while ((pa != nullptr) && (pb != nullptr))
	{
		q = new Node();
		m->next = q;
		char s = pa->data + pb->data;
		if (s > 9) // 处理进位
		{
			p->data += 1; // 进位
			for (p = p->next; p != q; p = p->next) // p、q 间节点置零
				p->data = 0;
			q->data = (char)(s - 10);
		}
		else if (s < 9) // 后移 p 到 q
		{ q->data = s; p = q; }
		// 等于 9 不用管
		m = q; //更新前一节点
		pa = pa->next; pb = pb->next;
	}
	// 如果最高位需要进位，那么，进位
	if (pc->data > 9)
	{
		p = new Node();
		p->data = 1; pc->data -= 10;
		p->next = pc; pc = p;
		carry = 1;
	}
	return pc;
}

int main()
{
	// printf("sizeof(Node): %llu", sizeof(Node)); // 16
	int const n = 10;
	char arr[n] = { 4, 9, 5, 3, 5, 6, 5, 6, 8, 1 };
	char brr[n] = { 5, 3, 0, 9, 7, 1, 9, 6, 4, 1 };
	int carry;
	Node* lsa; Node* lsb; Node* lsc;
	srand(static_cast<unsigned>(time(NULL)));
	printf("\nArray A:  ");
	for (int k = 0; k < n; ++k)
		printf("%d ", arr[k]);
	printf("\nArray B:  ");
	for (int k = 0; k < n; ++k)
		printf("%d ", brr[k]);
	lsa = mkList(arr, n); lsb = mkList(brr, n);
	lsc = listSum1(lsa, lsb, carry);
	if (carry == 0) printf("\n    Sum:  ");
	else printf("\n  Sum:  ");
	for (Node* pc = lsc; pc != nullptr; pc = pc->next)
		printf("%d ", pc->data);
	printf("\n\n");
	delList(lsa); delList(lsb); delList(lsc);
	return 0;
}
