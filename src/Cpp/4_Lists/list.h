#ifndef _LIST_H
#define _LIST_H

struct ListNode {
  int m_nValue;
  ListNode *m_pNext;
};

ListNode *CreateListNode(int value);
void ConnectListNodes(ListNode *pCurrent, ListNode *pNext);
void PrintListNode(ListNode *pNode);
void PrintList(ListNode *pHead);
void DestroyList(ListNode *pHead);
void AddToTail(ListNode **pHead, int value);
void RemoveNode(ListNode **pHead, int value);

#endif /* _LIST_H */