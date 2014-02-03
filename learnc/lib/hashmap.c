#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hashmap.h>
#include <linkedlist.h>
#include <keyedlinkedlist.h>

Node * * hashMapGetHead(HashMap* hashMap, char * key);
long stringHash(char * key, int primeModulus);

HashMap * hashMapCreate(int primeModulus)
{
  HashMap * hashMap = malloc(sizeof(HashMap));
  hashMap->primeModulus = primeModulus;
  hashMap->data = malloc(sizeof(Node) * primeModulus);
  memset((Node*)hashMap->data, 0, sizeof(Node) * primeModulus);
  return hashMap;
}

void hashMapPut(HashMap* hashMap, char * key, void * value)
{
  Node * * head = hashMapGetHead(hashMap, key);
  if (*head == NULL)
  {
	*head = (Node*)keyedListCreate(key, value);
  }
  else
  {
	keyedListAdd(*head, key, value);
  }
}

Node * * hashMapGetHead(HashMap* hashMap, char * key)
{  
  long index = stringHash(key, hashMap->primeModulus);
  return (Node * *)((Node *)hashMap->data)+index; 
}

void * hashMapGet(HashMap* hashMap, char * key)
{  
  Node * node = *hashMapGetHead(hashMap, key); 
  while (node != 0)
  {
    KeyValue * kv = node->data;
    if (strcmp(kv->key, key) == 0)
	{
	  return (long *)kv->value;
	}
	node = node->next;
  }  
  return 0;
}

long stringHash(char * s, int primeModulus)
{
  int h;
  char *t = s;
  for (h = 0; *t; t++)
  {
    h = (64*h + *t) % primeModulus;
  }
  return h;
}
