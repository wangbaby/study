
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x = 0, ListNode *next = nullptr) : val(x), next(next) {}
};

ListNode *createLinkedList(int *arr, size_t n) {
  if (n == 0)
    return nullptr;

  ListNode *head = new ListNode(arr[0]);
  ListNode *cur = head;
  for (int i = 1; i < n; i++) {
    cur->next = new ListNode(arr[i]);
    cur = cur->next;
  }

  return head;
}

void printLinkedList(ListNode *head) {
  while (head) {
    std::cout << head->val << " -> ";
    head = head->next;
  }

  std::cout << " NULL " << std::endl;
}

void deleteLinkedList(ListNode *head) {
  while (head) {
    ListNode *cur = head;
    head = cur->next;
    delete cur;
  }
}



pre cur next

多设立指针，保存更多信息

头结点

涉及到链表中头结点需要调整的：设立链表的虚拟头结点 dummyHead 注意删除
