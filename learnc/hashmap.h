#include <linkedlist.h>

typedef struct HASHMAP
{
  void * data;
  int primeModulus;
} HashMap;

void * hashMapGet(HashMap* hashMap, char * key);
HashMap * hashMapCreate(int primeModulus);
void hashMapPut(HashMap* hashMap, char * key, void * value);
void hashMapRemove(HashMap* hashMap, char * key);
void hashMapFree(HashMap* hashMap);
Node * hashMapGetValueList(HashMap* hashMap);
Node * hashMapGetKeyList(HashMap* hashMap);
