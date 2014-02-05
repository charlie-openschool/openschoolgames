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
  HashMap * map = hashMapCreate(11);
  hashMapPut(map, k1, &values[i++]);
  hashMapPut(map, k2, &values[i++]);
  hashMapPut(map, k3, &values[i++]);
  hashMapPut(map, k4, &values[i++]);
  hashMapPut(map, k5, &values[i++]);
  hashMapPut(map, k6, &values[i++]);
  
  v = hashMapGet(map, k1);

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
  assertIntEquals("testHashMap value 1", 1000, *v);
  v = hashMapGet(map, k2);
  assertIntEquals("testHashMap value 2", 1001, *v);
  v = hashMapGet(map, k3);
  assertIntEquals("testHashMap value 3", 1002, *v);
  v = hashMapGet(map, k4);
  assertIntEquals("testHashMap value 4", 1003, *v);
  v = hashMapGet(map, k5);
  assertIntEquals("testHashMap value 5", 1004, *v);
  v = hashMapGet(map, k6);
  assertIntEquals("testHashMap value 6", 1005, *v);
    v = hashMapGet(map, k6);
  assertIntEquals("testHashMap value 6", 1005, *v);
    v = hashMapGet(map, k7);
  assertIntEquals("testHashMap value 7", 1006, *v);
    v = hashMapGet(map, k8);
  assertIntEquals("testHashMap value 8", 1007, *v);
    v = hashMapGet(map, k9);
  assertIntEquals("testHashMap value 9", 1008, *v);
    v = hashMapGet(map, k10);
  assertIntEquals("testHashMap value 10", 1009, *v);
    v = hashMapGet(map, k11);
  assertIntEquals("testHashMap value 11", 1010, *v);
      v = hashMapGet(map, k12);
  assertIntEquals("testHashMap value 12", 1011, *v);
}

void testGetMissingKey()
{
  long * v = 0;
  char * k1 = "Hello";
  long value = 1000;
  HashMap * map = hashMapCreate(11);
  hashMapPut(map, k1, &value);
  v = hashMapGet(map, "xxx");
  assertIntEquals("testGetMissingKey", 0, (int)v);
  v = hashMapGet(map, k1);
  assertIntEquals("testGetMissingKey", 1000, *v);
}

void main(int argc, char* argv[])
{
  int numberOfTests = 4;
  void (*tests[numberOfTests])(void);
  tests[0] = testHashMapOneValue;
  tests[1] = testHashMapSixValues;
  tests[2] = testHashMapTwelveValues;
  tests[3] = testGetMissingKey;

  int i = 0;
  while (i < numberOfTests)
  {
    tests[i]();
	printf("\n");
	i++;
  }

return;
}