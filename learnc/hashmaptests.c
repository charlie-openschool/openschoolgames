#include <strings.h>
#include <hashmap.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <testasserts.h>
#include <linkedlist.h>

void testHashMapOneValue()
{
  HashMap * map = hashMapCreate(11);
  long value = 1999;
  hashMapPut(map, "Hello", &value);
  long * p = hashMapGet(map, "Hello");
  assertIntEquals("testHashMapOneValue", 1999, *p);

  // cleanup
  hashMapRemove(map, "Hello");
  hashMapFree(map);
  map = NULL;
  
}

void testHashMapSixValues()
{
  long * v = 0;
  long values[] = {1000, 1001,1002,1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012};
  char * k1 = "Hello";
  char * k2 = "hello";
  char * k3 = "world";
  char * k4 = "World";
  char * k5 = "good";
  char * k6 = "bye";
  int i = 0;
  HashMap * map = hashMapCreate(3);
  hashMapPut(map, k1, &values[i++]);
  hashMapPut(map, k2, &values[i++]);
  hashMapPut(map, k3, &values[i++]);
  hashMapPut(map, k4, &values[i++]);
  hashMapPut(map, k5, &values[i++]);
  hashMapPut(map, k6, &values[i++]);
  
  v = hashMapGet(map, k1);

  assertIntEquals("testHashMapSixValues value 1", 1000, *v);
  v = hashMapGet(map, "hello");
  assertIntEquals("testHashMapSixValues value 2", 1001, *v);
  v = hashMapGet(map, "world");
  assertIntEquals("testHashMapSixValues value 3", 1002, *v);
  v = hashMapGet(map, "World");
  assertIntEquals("testHashMapSixValues value 4", 1003, *v);
  v = hashMapGet(map, "good");
  assertIntEquals("testHashMapSixValues value 5", 1004, *v);
  v = hashMapGet(map, "bye");
  assertIntEquals("testHashMapSixValues value 6", 1005, *v);
  hashMapFree(map);
  map = NULL;
}

void testHashMapRemoveSixValues()
{
  long * v = 0;
  long values[] = {1000, 1001,1002,1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012};
  char * k1 = "Hello";
  char * k2 = "hello";
  char * k3 = "world";
  char * k4 = "World";
  char * k5 = "good";
  char * k6 = "bye";
  int i = 0;
  HashMap * map = hashMapCreate(11);
  hashMapPut(map, k1, &values[i++]);
  hashMapPut(map, k2, &values[i++]);
  hashMapPut(map, k3, &values[i++]);
  hashMapPut(map, k4, &values[i++]);
  hashMapPut(map, k5, &values[i++]);
  hashMapPut(map, k6, &values[i++]);
  hashMapRemove(map, k1);
  hashMapRemove(map, k2);
  hashMapRemove(map, k3);
  hashMapRemove(map, k4);
  hashMapRemove(map, k5);
  hashMapRemove(map, k6);
  v = hashMapGet(map, k1);
  assertIntEquals("testHashMapRemoveSixValues value 1", 0, (int)v);
  v = hashMapGet(map, "hello");
  assertIntEquals("testHashMapRemoveSixValues value 2", 0, (int)v);
  v = hashMapGet(map, "world");
  assertIntEquals("testHashMapRemoveSixValues value 3", 0, (int)v);
  v = hashMapGet(map, "World");
  assertIntEquals("testHashMapRemoveSixValues value 4", 0, (int)v);
  v = hashMapGet(map, "good");
  assertIntEquals("testHashMapRemoveSixValues value 5", 0, (int)v);
  v = hashMapGet(map, "bye");
  assertIntEquals("testHashMapRemoveSixValues value 6", 0, (int)v);

  hashMapFree(map);
  map = NULL;
}

void testHashMapTwelveValues()
{
  long * v = 0;
  char * k1 = "Hello";
  char * k2 = "hello";
  char * k3 = "world";
  char * k4 = "World";
  char * k5 = "good";
  char * k6 = "bye";
  char * k7 = "a";
  char * k8 = "b";
  char * k9 = "c";
  char * k10 = "d";
  char * k11 = "e";
  char * k12 = "f";
  long values[] = {1000, 1001,1002,1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012}; 
  int i = 0;
  HashMap * map = hashMapCreate(11);
  hashMapPut(map, k1, &values[i++]);
  hashMapPut(map, k2, &values[i++]);
  hashMapPut(map, k3, &values[i++]);
  hashMapPut(map, k4, &values[i++]);
  hashMapPut(map, k5, &values[i++]);
  hashMapPut(map, k6, &values[i++]);
  hashMapPut(map, k7, &values[i++]);
  hashMapPut(map, k8, &values[i++]);
  hashMapPut(map, k9, &values[i++]);
  hashMapPut(map, k10, &values[i++]);
  hashMapPut(map, k11, &values[i++]);
  hashMapPut(map, k12, &values[i++]);
  v = hashMapGet(map, k1);
  assertIntEquals("testHashMapTwelveValues value 1", 1000, *v);
  v = hashMapGet(map, k2);
  assertIntEquals("testHashMapTwelveValues value 2", 1001, *v);
  v = hashMapGet(map, k3);
  assertIntEquals("testHashMapTwelveValues value 3", 1002, *v);
  v = hashMapGet(map, k4);
  assertIntEquals("testHashMapTwelveValues value 4", 1003, *v);
  v = hashMapGet(map, k5);
  assertIntEquals("testHashMapTwelveValues value 5", 1004, *v);
  v = hashMapGet(map, k6);
  assertIntEquals("testHashMapTwelveValues value 6", 1005, *v);
  v = hashMapGet(map, k6);
  assertIntEquals("testHashMapTwelveValues value 6", 1005, *v);
  v = hashMapGet(map, k7);
  assertIntEquals("testHashMapTwelveValues value 7", 1006, *v);
  v = hashMapGet(map, k8);
  assertIntEquals("testHashMapTwelveValues value 8", 1007, *v);
  v = hashMapGet(map, k9);
  assertIntEquals("testHashMapTwelveValues value 9", 1008, *v);
  v = hashMapGet(map, k10);
  assertIntEquals("testHashMapTwelveValues value 10", 1009, *v);
  v = hashMapGet(map, k11);
  assertIntEquals("testHashMapTwelveValues value 11", 1010, *v);
  v = hashMapGet(map, k12);
  assertIntEquals("testHashMapTwelveValues value 12", 1011, *v);
  hashMapFree(map);
  map = NULL;
}

void testHashMapGetMissingKey()
{
  long * v = 0;
  char * k1 = "Hello";
  long value = 1000;
  HashMap * map = hashMapCreate(11);
  hashMapPut(map, k1, &value);
  v = hashMapGet(map, "xxx");
  assertIntEquals("testHashMapGetMissingKey", 0, (int)v);
  v = hashMapGet(map, k1);
  assertIntEquals("testHashMapGetMissingKey", 1000, *v);
  hashMapFree(map);
  map = NULL;
}

void main(int argc, char* argv[])
{
  Node * head = linkedListCreate(testHashMapOneValue);
  linkedListAdd(head, testHashMapSixValues);
  linkedListAdd(head, testHashMapTwelveValues);
  linkedListAdd(head, testHashMapGetMissingKey);
  linkedListAdd(head, testHashMapRemoveSixValues);
  Node * testNode = head;    
  while (testNode != NULL)
  {
    ((void (*)(void))testNode->data)();
	printf("\n");
    testNode = testNode->next;
  }
  
  testNode = head;
  while(testNode != NULL)
  {
    testNode = linkedListRemove(head, testNode);
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
   
  return;
}