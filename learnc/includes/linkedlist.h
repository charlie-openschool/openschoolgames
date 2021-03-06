#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct NODE
{
  void * data;
  struct NODE * next;
}Node;


Node * linkedListCreate(void * data);
Node * linkedListRemove(Node * head, Node * node);
Node * linkedListInsert(Node * current, void * data);
Node * linkedListAdd(Node * head, void * data);
void linkedListFree(Node * head);

#endif
