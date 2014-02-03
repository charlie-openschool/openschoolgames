int main()
{
  long d1 = 1;
  long d2 = 2;
  long d3 = 3;
  Node * head = linkedListCreate(&d1);
  long  * p = head->data;
  printf("d1: %d\n", *p);
  Node * node = linkedListAdd(head, &d2);
  Node * node2 = linkedListRemove(head, head);
  p = node->data;
  printf("d2: %d\n", *p);
  p = node2->data;
  printf("d2: %d\n", *p);
  Node * node3 = linkedListAdd(node, &d3);
  Node * current = linkedListCreate(&d1);
  current->next = node;
  while (current != NULL)
  {
    printf("current: %d\n", *((long *)current->data));
    current = current->next;
  }

  return 0;	

}
