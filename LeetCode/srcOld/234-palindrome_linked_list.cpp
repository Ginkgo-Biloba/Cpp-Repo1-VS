class Solution
{
public:
  ListNode* rev(ListNode* head)
  {
    ListNode* p = nullptr, *q;
    
    while(head)
    {
      q = head->next;
      head->next = p;
      p = head;
      head = q;
    }
    
    return p;
  }
  
  
  
  bool isPalindrome(ListNode* head) 
  {
    ListNode* p = head, *q, *left, *right;
    int len = 0, half;
    if (head == nullptr || head->next == nullptr)
      return true;
    
    ++len;
    for (; p->next != nullptr; p = p->next)
      ++len;
    
    // 断开的地方
    left = nullptr; right = head;
    for(half = (len + 1) / 2; half > 0; --half)
    {
      left = right; 
      right = right->next;
    }
    left->next = nullptr;
    
    p = head;
    q = rev(right);  
    while(q && p->val == q->val)
    {
      p = p->next; 
      q = q->next;
    }
    
    left->next = rev(q);
    
    return q == nullptr;
  }
};
