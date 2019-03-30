class Solution {
public:
  void reorderList(ListNode* head)
  {
    ListNode dummy(0);
    ListNode* slow = head, *fast = head;
    
    // len <= 2 不操作
    if(!(head && head->next && head->next->next))
      return;
    
    // 找到中点
    while (fast && fast->next)
    {
      slow = slow->next;
      fast = fast->next->next;
    }
    // 断开
    fast = slow->next;
    slow->next = nullptr;
    
    // 翻转后半部分
    ListNode* prev = nullptr;
    if (fast && fast->next)
    {
      while (fast)
      {
        ListNode* next = fast->next;
        fast->next = prev;
        prev = fast;
        fast = next;
      }
      fast = prev;
    }
    
    // 合并
    slow = head;
    prev = &dummy;
    while (slow && fast)
    {
      ListNode* s = slow->next, *f = fast->next;
      prev->next = slow;
      prev->next->next = fast;
      prev = fast;
      slow = s; fast = f;
    }
    // 奇数情况
    if (slow)
      prev->next = slow;
    
    head = dummy.next;
  }
};