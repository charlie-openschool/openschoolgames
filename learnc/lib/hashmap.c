#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hashmap.h>

long stringHash(char * key, int primeModulus);
long * hashMapGet(HashMap* hashMap, char * key);
Node * hashMapGetHead(HashMap* hashMap, char * key);
Node * createLinkedList(char * key, long * data);
Node * linkedListInsert(Node * node, char * key, long * data);
void linkedListRemove(Node * head, Node * node);
void linkedListRemoveByKey(Node * head, char * key);
Node * linkedListAdd(Node * head, char * key, long * data);
Node * linkedListGet(Node * head, char * key);

Node * linkedListGet(Node * head, char * key)
{
  Node * current = head;
  while (current->next != 0)
  {
    if (strcmp(current->key, key) == 0)
	{
	  return current;
	}
    current = current->next;
  }
  return 0;
}

Node * linkedListInsert(Node * node, char * key, long * data)
{
  Node * insertedNode = createLinkedList(key, data);
  Node * next = node->next;
  node->next = insertedNode;
  insertedNode->next = next;
  return insertedNode;
}

Node * createLinkedList(char * key, long * data)
{
  Node * node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->key = key;
  node->next = 0;
  return node;
}

void linkedListRemove(Node * head, Node * node)
{
  Node * current = head;
  while (current->next != node)
  {
    current = current->next;
  }
  current->next = node->next;
  node->data = 0;
  node->next = 0;
  free(node);
}

void linkedListRemoveByKey(Node * head, char * key)
{
  Node * current = head;
  while (current->next != 0 && strcmp(current->next->key, key) != 0)
  {
    current = current->next;
  }
  if (current->next != 0)
  {
    Node * toFree = current->next;
    current->next = current->next->next;
    toFree->data = 0;
    toFree->next = 0;
    free(toFree);
  }
}

Node * linkedListAdd(Node * head, char * key, long * data)
{
  Node * current = head;
  while (current->next != 0)
  {
    current = current->next;
  }
  current->next = createLinkedList(key, data);
  return current->next;
}

HashMap * hashMapCreate(int primeModulus)
{
  HashMap * hashMap = (HashMap *)malloc(sizeof(HashMap));
  hashMap->primeModulus = primeModulus;
  hashMap->data = (long*)malloc(sizeof(long*) * primeModulus);
  memset(hashMap->data, 0, sizeof(long*) * primeModulus);
  return hashMap;
}

void hashMapPut(HashMap* hashMap, char * key, long value)
{
  long * ptr = (long *)malloc(sizeof(long));
  *ptr = value;
  Node * head = hashMapGetHead(hashMap, key);
  if (head == NULL)
  {
    long index = stringHash(key, hashMap->primeModulus);
	head = (Node*)createLinkedList(key, ptr);
    *(hashMap->data+index) = (long)head;
  }
  else
  {
	linkedListAdd(head, key, ptr);
  }
}

Node * hashMapGetHead(HashMap* hashMap, char * key)
{  
  long index = stringHash(key, hashMap->primeModulus);
  return (Node *)*(hashMap->data+index); 
}

long * hashMapGet(HashMap* hashMap, char * key)
{  
  long index = stringHash(key, hashMap->primeModulus);
  long * n = (long *)hashMap->data+index; 
  int listCount = 0;
   Node * node = (Node *)*n;
  while (node != 0)
  {
    if (strcmp(node->key, key) == 0)
	{
	  return (long *)node->data;
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