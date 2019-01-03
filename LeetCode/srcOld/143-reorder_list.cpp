class Solution {
public:
  void reorderList(ListNode* head)
  {
    ListNode dummy(0);
    ListNode* slow = head, *fast = head;
    
    // len <= 2 ������
    if(!(head && head->next && head->next->next))
      return;
    
    // �ҵ��е�
    while (fast && fast->next)
    {
      slow = slow->next;
      fast = fast->next->next;
    }
    // �Ͽ�
    fast = slow->next;
    slow->next = nullptr;
    
    // ��ת��벿��
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
    
    // �ϲ�
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
    // �������
    if (slow)
      prev->next = slow;
    
    head = dummy.next;
  }
};