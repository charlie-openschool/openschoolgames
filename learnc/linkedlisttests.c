#include <stdio.h>
#include <linkedlist.h>
#include <testasserts.h>

void testCreate()
{
  long d1 = 1;
  Node * current = linkedListCreate(&d1);
  assertIntEquals("testCreate value 1", 1, *(long *)current->data);
  assertIntEquals("testCreate tail", 0, (long)current->next);
}

void testAdd()
{
  long d1 = 1;
  long d2 = 2;
  Node * head = linkedListCreate(&d1);
  linkedListAdd(head, &d2);
  Node * current = head;
  assertIntEquals("testAdd value 1", 1, *(long *)current->data);
  current = current->next;
  assertIntEquals("testAdd value 2", 2, *(long *)current->data);  
}

void testRemoveHead()
{
  long d1 = 1;
  long d2 = 2;
  long d3 = 3;
  Node * head = linkedListCreate(&d1);
  linkedListAdd(head, &d2);
  linkedListAdd(head, &d3);
  Node * current = head;
  linkedListRemove(head, current);
  assertIntEquals("testRemoveHead value 2", 2, *(long *)current->data);
  current = current->next;
  assertIntEquals("testRemoveHead value 3", 3, *(long *)current->data);
  current = current->next;
  assertIntEquals("testRemoveHead null tail", 0, (long)current); 
}

void testRemoveTail()
{
  long d1 = 1;
  long d2 = 2;
  long d3 = 3;
  Node * head = linkedListCreate(&d1);
  linkedListAdd(head, &d2);
  Node * tail = linkedListAdd(head, &d3);
  linkedListRemove(head, tail);
  Node * current = head; 
  assertIntEquals("testRemoveTail value 1", 1, *(long *)current->data);
  current = current->next;
  assertIntEquals("testRemoveTail value 2", 2, *(long *)current->data);
  current = current->next;
  assertIntEquals("testRemoveTail null tail", 0, (long)current);
}

void testRemoveMid()
{
  long d1 = 1;
  long d2 = 2;
  long d3 = 3;
  Node * head = linkedListCreate(&d1);
  Node * mid = linkedListAdd(head, &d2);
  linkedListAdd(head, &d3);
  linkedListRemove(head, mid);
  Node * current = head;
  assertIntEquals("testRemoveMid value 1", 1, *(long *)current->data);
  current = current->next;
  assertIntEquals("testRemoveMId value 3", 3, *(long *)current->data);
  current = current->next;
  assertIntEquals("testRemoveTail null tail", 0, (long)current);
}


void test()
{
  // placeholder
}

void testAddTwo()
{
  long d1 = 1;
  long d2 = 2;
  long d3 = 3;
  Node * head = linkedListCreate(&d1);
  Node * node2 = linkedListAdd(head, &d2);
  Node * node3 = linkedListAdd(head, &d3);
  assertIntEquals("testAddTwo value 1", 1, *(long *)head->data);
  assertIntEquals("testAddTwo value 2", 2, *(long *)node2->data);
  assertIntEquals("testAddTwo value 3", 3, *(long *)node3->data);
  assertIntEquals("testAddTwo null tail", 0, (long)node3->next);
}

void testInsert()
{

  long d1 = 1;
  long d2 = 2;
  long d3 = 3;
  long d4 = 4;
  Node * head = linkedListCreate(&d1);
  Node * node2 = linkedListAdd(head, &d2);
  Node * node3 = linkedListAdd(head, &d3);
  Node * node4 = linkedListInsert(node2, &d4);
  assertIntEquals("testInsert value 1", 1, *(long *)head->data);
  assertIntEquals("testInsert value 2", 2, *(long *)node2->data);
  assertIntEquals("testInsert value 4", 4, *(long *)node2->next->data);
  assertIntEquals("testInsert value 3", 3, *(long *)node3->data);
  assertIntEquals("testInsert value 4", 4, *(long *)node4->data);
  assertIntEquals("testInsert null tail", 0, (long)node3->next);
}

void testIterate()
{
  long d1 = 1;
  long d2 = 2;
  long d3 = 3;
  long d4 = 4;
  Node * head = linkedListCreate(&d1);
  linkedListAdd(head, &d2);
  linkedListAdd(head, &d3);
  int size = 0;
  Node * current = head;
  while (current != NULL)
  {
    size++;
    current = current->next;
  }
  assertIntEquals("testIterate size", 3, size);
}

void testRemoveInserted()
{
  long d1 = 1;
  long d2 = 2;
  long d3 = 3;
  long d4 = 4;
  Node * head = linkedListCreate(&d1);
  Node * node2 = linkedListAdd(head, &d2);
  linkedListAdd(head, &d3);
  Node * node4 = linkedListInsert(node2, &d4); 
 linkedListRemove(head, node4);
  Node * current = head;
  assertIntEquals("testRemoveInserted value 1", 1, *(long *)current->data);
  current = current->next;
  assertIntEquals("testRemoveInserted value 2", 2, *(long *)current->data);
  current = current->next;
  assertIntEquals("testRemoveInserted value 3", 3, *(long *)current->data);
  current = current->next;
  assertIntEquals("testRemoveInserted null tail", 0, (long)current);
}

int main()
{
  int numberOfTests = 13;
  void (*tests[numberOfTests])(void);
  tests[0] = testCreate;
  tests[1] = testAdd;
  tests[2] = testAddTwo;
  tests[3] = testInsert;
  tests[4] = testIterate;
  tests[5] = testRemoveHead;
  tests[6] = testRemoveMid;
  tests[7] = testRemoveTail;
  tests[8] = testRemoveInserted;
  tests[9] = test;
  tests[10]= test;
  tests[11]= test;
  tests[12]= test;
  int i = 0;
  while (i < numberOfTests)
  {
    tests[i]();
    printf("\n");
    i++;
  }

  printf("%d asserts successful.\n", assertsGetTotal());
  if (assertsGetFailures() > 0)
  {
    printf("%d asserts failed.\n", assertsGetFailures());
  }
  else
  {
    printf("All tests successful.\n");
  }

  return 0;	

}
