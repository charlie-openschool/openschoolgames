#include <stdio.h>
#include <keyedlinkedlist.h>
#include <testasserts.h>

void test()
{ // place holder
}

void testCreate()
{
 int one = 1;
 
  Node* head = keyedListCreate("FIRST", &one);
  Node* t = head;
  assertStrEquals("testCreate key one", "FIRST", (char *)((KeyValue*)t->data)->key);
  assertIntEquals("testCreate value one", 1, *(int *)((KeyValue*)t->data)->value);
}

void testAdd()
{
  int one = 1;
  int two = 2;
  int three = 3;
  int twentyTwo = 22;
  Node* n1 = keyedListCreate("FIRST", &one);
  Node* n2 = keyedListAdd(n1, "SECOND", &two);
  Node* n3 = keyedListAdd(n2, "THIRD", &three);
  Node* t = n1;
  assertStrEquals("testAdd key one", "FIRST", (char *)((KeyValue*)t->data)->key);
  assertIntEquals("testAdd value one", 1, *(int *)((KeyValue*)t->data)->value);
  t = n2;
  assertStrEquals("testAdd key two", "SECOND", (char *)((KeyValue*)t->data)->key);
  assertIntEquals("testAdd value two", 2, *(int *)((KeyValue*)t->data)->value);
  t = n3;
  assertStrEquals("testAdd key one", "THIRD", (char *)((KeyValue*)t->data)->key);
  assertIntEquals("testAdd value three", 3, *(int *)((KeyValue*)t->data)->value);
}

/**
  test iterate
  start with the head and walk the entire list
*/
void testIterate()
{
  int one = 1;
  int two = 2;
  int three = 3;
  int twentyTwo = 22;
  Node* head = keyedListCreate("FIRST", &one);
  Node* p = keyedListAdd(head, "SECOND", &two);
  keyedListAdd(head, "THIRD", &three);
  Node* t = head;
  assertStrEquals("testIterate key FIRST", "FIRST", (char *)((KeyValue*)t->data)->key);
  assertIntEquals("testIterate value 1", 1, *(int *)((KeyValue*)t->data)->value);
  t = t->next;
  assertStrEquals("testIterate key SECOND", "SECOND", (char *)((KeyValue*)t->data)->key);
  assertIntEquals("testIterate value 2", 2, *(int *)((KeyValue*)t->data)->value);
  t = t->next;
  assertStrEquals("testIterate key THIRD", "THIRD", (char *)((KeyValue*)t->data)->key);
  assertIntEquals("testIterate value 3", 3, *(int *)((KeyValue*)t->data)->value);
  t = t->next;
  assertIntEquals("testIterate tail next null", 0, (int)t);
}

/**
  test get
  get each node by key
*/
void testGet()
{
  int one = 1;
  int two = 2;
  int three = 3;
  int twentyTwo = 22;
  Node* head = keyedListCreate("FIRST", &one);
  Node* p = keyedListAdd(head, "SECOND", &two);
  keyedListAdd(head, "THIRD", &three);
     
  KeyValue* kv = keyedListGet(head, "SECOND");
  assertStrEquals("testGet key SECOND", "SECOND", (char *)kv->key);
  assertIntEquals("testGet value 2", 2, *(int *)kv->value);
  
  kv = keyedListGet(head, "FIRST");
  assertStrEquals("testGet key FIRST", "FIRST", (char *)kv->key);
  assertIntEquals("testGet value 1", 1, *(int *)kv->value);
  
  // we can search the list from any node before or equal to the target node
  kv = keyedListGet(head->next, "THIRD");
  assertStrEquals("testGet key THIRD", "THIRD", (char *)kv->key);
  assertIntEquals("testGet value 3", 3, *(int *)kv->value);
  
  kv = keyedListGet(head->next->next, "THIRD");
  assertStrEquals("testGet key THIRD", "THIRD", (char *)kv->key);
  assertIntEquals("testGet value 3", 3, *(int *)kv->value);
}

void testInsert()
{
  int one = 1;
  int two = 2;
  int three = 3;
  int twentyTwo = 22;
  Node* head = keyedListCreate("FIRST", &one);
  keyedListAdd(head, "SECOND", &two);
  keyedListAdd(head, "THIRD", &three);
  Node* t = head; 
  keyedListInsert(head->next, "SECOND A", &twentyTwo);
  
  t = head;
  KeyValue* kv = t->data;
  assertStrEquals("testInsert one", "FIRST", (char *)kv->key);
  assertIntEquals("testInsert value one", 1, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testInsert two", "SECOND", (char *)kv->key);
  assertIntEquals("testInsert value two", 2, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testInsert inserted", "SECOND A", (char *)kv->key);
  assertIntEquals("testInsert value inserted", 22, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testInsert three", "THIRD", (char *)kv->key);
  assertIntEquals("testInsert value three", 3, *(int *)kv->value);
  
}

void testRemoveHead()
{
  int one = 1;
  int two = 2;
  int three = 3;
  int twentyTwo = 22;
  Node* head = keyedListCreate("FIRST", &one);
  keyedListAdd(head, "SECOND", &two);
  keyedListAdd(head, "THIRD", &three);
  Node* t = head; 
  
  keyedListRemove(head, "FIRST");
  // head must always be valid otherwise any place in code that was holding onto the list would no
  // longer have a valid pointer to the list.
  KeyValue* kv = t->data;
  // head now points to what was the second element in the list
  assertStrEquals("testRemoveHead SECOND", "SECOND", (char *)kv->key);
  assertIntEquals("testRemoveHead value 2", 2, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testRemoveHead THIRD", "THIRD", (char *)kv->key);
  assertIntEquals("testRemoveHead value 3", 3, *(int *)kv->value);  
}

void testRemoveMid()
{
  int one = 1;
  int two = 2;
  int three = 3;
  int twentyTwo = 22;
  Node* head = keyedListCreate("FIRST", &one);
  keyedListAdd(head, "SECOND", &two);
  keyedListAdd(head, "THIRD", &three);
  Node* t = head; 
  keyedListInsert(head->next, "SECOND A", &twentyTwo);
  
  // move the head pointer all the way to the node before the node which has key THIRD and remove it.
  keyedListRemove(head->next->next, "THIRD");
  
  KeyValue* kv = t->data;
  assertStrEquals("testRemoveMid FIRST", "FIRST", (char *)kv->key);
  assertIntEquals("testRemoveMid value 1", 1, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testRemoveMid SECOND", "SECOND", (char *)kv->key);
  assertIntEquals("testRemoveMid value 2", 2, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testRemoveMid inserted", "SECOND A", (char *)kv->key);
  assertIntEquals("testRemoveMid value inserted 22", 22, *(int *)kv->value);
  t = t->next;
  assertIntEquals("testRemoveMid end of list", 0, (int)t); 
}

void testRemoveTail()
{
  int one = 1;
  int two = 2;
  int three = 3;
  int twentyTwo = 22;
  Node* head = keyedListCreate("FIRST", &one);
  keyedListAdd(head, "SECOND", &two);
  keyedListAdd(head, "THIRD", &three);
  Node* t = head; 
  keyedListInsert(head->next, "SECOND A", &twentyTwo);
  
  t = head;
  KeyValue* kv = t->data;
  assertStrEquals("testRemoveTail FIRST", "FIRST", (char *)kv->key);
  assertIntEquals("testRemoveTail value 1", 1, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testRemoveTail SECOND", "SECOND", (char *)kv->key);
  assertIntEquals("testRemoveTail value 2", 2, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testRemoveTail inserted", "SECOND A", (char *)kv->key);
  assertIntEquals("testRemoveTail value inserted", 22, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testRemoveTail THIRD", "THIRD", (char *)kv->key);
  assertIntEquals("testRemoveTail value 3", 3, *(int *)kv->value);
  
}

void testRemoveInserted()
{
  int one = 1;
  int two = 2;
  int three = 3;
  int twentyTwo = 22;
  Node* head = keyedListCreate("FIRST", &one);
  keyedListAdd(head, "SECOND", &two);
  keyedListAdd(head, "THIRD", &three);
  Node* t = head; 
  keyedListInsert(head->next, "SECOND A", &twentyTwo);
  keyedListRemove(head, "SECOND A");
  t = head;
  KeyValue* kv = t->data;
  assertStrEquals("testRemoveInserted FIRST", "FIRST", (char *)kv->key);
  assertIntEquals("testRemoveInserted value 1", 1, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testRemoveInserted SECOND", "SECOND", (char *)kv->key);
  assertIntEquals("testRemoveInserted value 2", 2, *(int *)kv->value);
  t = t->next;
  kv = t->data;
  assertStrEquals("testRemoveInserted THIRD", "THIRD", (char *)kv->key);
  assertIntEquals("testRemoveInserted value 3", 3, *(int *)kv->value);
  
}

int main()
{
  int numberOfTests = 13;
  void (*tests[numberOfTests])(void);
  tests[0] = testCreate;
  tests[1] = testAdd;
  tests[2] = testGet;
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
