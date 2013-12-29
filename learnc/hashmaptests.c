#include <strings.h>
#include <hashmap.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <testasserts.h>

void testHashMapOneValue()
{
  HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  hashMapInit(map, 101);;
  hashMapPut(map, "Hello", 1000);
  long * p = hashMapGet(map, "Hello");
  assertIntEquals("testHashMap", 1000, *p);
}

void testHashMapSixValues()
{
  HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  hashMapInit(map, 101);
  hashMapPut(map, "Hello", 1000);
  hashMapPut(map, "hello", 1001);
  hashMapPut(map, "world", 1002);
  hashMapPut(map, "World", 1003);
  hashMapPut(map, "good", 1004);
  hashMapPut(map, "bye", 1005);
  long * v = hashMapGet(map, "Hello");
  assertIntEquals("testHashMap value 1", 1000, *v);
  v = hashMapGet(map, "hello");
  assertIntEquals("testHashMap value 2", 1001, *v);
  v = hashMapGet(map, "world");
  assertIntEquals("testHashMap value 3", 1002, *v);
  v = hashMapGet(map, "World");
  assertIntEquals("testHashMap value 4", 1003, *v);
  v = hashMapGet(map, "good");
  assertIntEquals("testHashMap value 5", 1004, *v);
  v = hashMapGet(map, "bye");
  assertIntEquals("testHashMap value 6", 1005, *v);
}

void testLinkedListInsert()
{
  long d1 = 2001;
  long d2 = 2002;
  long d3 = 2003;
  long d4 = 2004;
  Node * head = createLinkedList("d1",&d1);
  Node * node = linkedListAdd(head, "d2",&d2);
  linkedListAdd(head, "d4",&d4);
  linkedListInsert(node, "d3", &d3);
  node = head;
  assertIntEquals("testLinkListInsert value 1", 2001,*node->data);
  node = node->next;  
  assertIntEquals("testLinkListInsert value 2", 2002,*node->data);
  node = node->next;  
  assertIntEquals("testLinkListInsert value 3", 2003,*node->data);
  node = node->next;  
  assertIntEquals("testLinkListInsert value 4", 2004,*node->data);
}

void testLinkedList()
{
  long d1 = 2001;
  long d2 = 2002;
  long d3 = 2003;
  long d4 = 2004;
  long d5 = 2005;
  Node * head = createLinkedList("d1",&d1);
  Node * node = linkedListAdd(head, "d2",&d2);
  linkedListAdd(head, "d3",&d3);
  linkedListAdd(head, "d4", &d4);
  node = head;
  assertIntEquals("testLinkList value 1", 2001,*node->data);
  node = node->next;  
  assertIntEquals("testLinkList value 2", 2002,*node->data);
  node = node->next;  
  assertIntEquals("testLinkList value 3", 2003,*node->data);
  node = node->next;  
  assertIntEquals("testLinkList value 4", 2004,*node->data);
  node->next = createLinkedList("d5", &d5);
  node = node->next;  
  assertIntEquals("testLinkList value 5", 2005,*node->data);
}

void testLinkedListRemove()
{
  long d1 = 2001;
  long d2 = 2002;
  long d3 = 2003;
  long d4 = 2004;
  long d5 = 2005;
  Node * head = createLinkedList("d1",&d1);
  linkedListAdd(head, "d2",&d2);
  linkedListAdd(head, "d3",&d3);
  linkedListAdd(head, "d4", &d4);
  linkedListAdd(head, "d5", &d5);
  Node * node = head;
  
  linkedListRemove(head, head->next);
  assertIntEquals("testLinkListRemove value 1", 2001,*node->data);
  node = node->next;  
  assertIntEquals("testLinkListRemove value 3", 2003,*node->data);
  node = node->next;  
  assertIntEquals("testLinkListRemove value 4", 2004,*node->data);
  node = node->next;  
  assertIntEquals("testLinkListRemove value 5", 2005,*node->data);
 }
 
void testLinkedListRemoveByKey()
{
  long d1 = 2001;
  long d2 = 2002;
  long d3 = 2003;
  long d4 = 2004;
  long d5 = 2005;
  Node * head = createLinkedList("d1",&d1);
  Node * node = linkedListAdd(head, "d2",&d2);
  linkedListAdd(head, "d3",&d3);
  linkedListAdd(head, "d4", &d4);
  linkedListAdd(head, "d5", &d5);
  linkedListRemoveByKey(head, "d3");
  linkedListRemoveByKey(head, "d5");
  node = head;
  assertIntEquals("testLinkListRemoveByKey value 1", 2001,*node->data);
  node = node->next;
  assertIntEquals("testLinkListRemoveByKey value 2", 2002,*node->data);
  node = node->next;    
  assertIntEquals("testLinkListRemoveByKey value 4", 2004,*node->data);
  node = node->next;  
  assertIntEquals("testLinkListRemoveByKey node null", 0, (int)node);
}

void main(int argc, char* argv[])
{
  int numberOfTests = 6;
  void (*tests[numberOfTests])(void);
  tests[0] = testHashMapOneValue;
  tests[1] = testHashMapSixValues;
  tests[2] = testLinkedList;
  tests[3] = testLinkedListInsert;
  tests[4] = testLinkedListRemoveByKey;
  tests[5] = testLinkedListRemove;
/*  tests[6] = testLength;
  tests[7] = testLengthNull;
  tests[8] = testStringConcat;
  tests[9] = testEchoStrings;
  tests[10]= testSplit;
  tests[11]= testSplitOneWord;
  tests[12]= testSplitNull;*/
  int i = 0;
  while (i < numberOfTests)
  {
    tests[i]();
	printf("\n");
	i++;
  }

return;

  HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  hashMapInit(map, 101);  
  i = 0;
  char * keys = (char *)malloc(sizeof(char) * 1001 * 5);
  char * kp = keys;
  while (i < 1001)
  {
    char * key = getRandomString(5);
	char * t = key;
	int cnt = 0;
	while (cnt < 5)
	{
	  *kp = *t;
	  kp++;
	  t++;
	  cnt++;
	}
	hashMapPut(map, key, 5000 + i);
	i++;
  }
  i = 0;
  char * tKey = keys;
  while (i < 1001)
  {
    char * key = (char *)malloc(sizeof(char) * 6);
	char * tK = key;
	int cnt = 0;
	while (cnt < 5)
	{
	  *tK = *tKey;
	  tK++;
	  tKey++;
	  cnt++;
	}
	*tK = '\0';
	long * pV = hashMapGet(map, key);
	printf("Map value at %s is %d\n", key, *pV);
	i++;
  }
}