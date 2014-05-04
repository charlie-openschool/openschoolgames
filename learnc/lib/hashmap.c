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
  hashMap->data = malloc(sizeof(Node*) * primeModulus);
  memset((Node*)hashMap->data, 0, sizeof(Node*) * primeModulus);
  return hashMap;
}


/**
   cleans up all memory for the hashMap and the lists that it uses.
   does not clean up any keys or values as this belong to the user.
*/
void hashMapFree(HashMap* hashMap)
{
   Node * data = hashMap->data;
   int index = 0;
   while (index < hashMap->primeModulus)
   {
     Node * node = *((Node * *)((Node *)hashMap->data)+index);
     if (node != NULL)
     {
        while (node != NULL)
        {
          KeyValue * kv = node->data;
          // The memory for both key and value belong to the consumer
          free(kv);
          Node * temp = node->next;
          free(node);
          node = temp;
        } 
     } 
     index++;
   }
   memset((Node*)hashMap->data, 0, sizeof(Node*) * hashMap->primeModulus);
   free(hashMap->data);
   hashMap->data = 0;   
   free(hashMap);
}


/**
* Get the head node to a list of all values in the map
*/
Node * hashMapGetValueList(HashMap* hashMap)
{
   Node * data = hashMap->data;
   Node * head = NULL;
   int index = 0;
   while (index < hashMap->primeModulus)
   {
     Node * node = *((Node * *)((Node *)hashMap->data)+index);
     if (node != NULL)
     {
        while (node != NULL)
        {
          KeyValue * kv = node->data;
          if (head == NULL)
          {
            head = linkedListCreate(kv->value);
          }
          else
          {
            linkedListAdd(head, kv->value);
          }
          node = node->next;
        } 
     } 
     index++;
   }
  return head;
}

/**
* Get the head node to a list of all keys in the map
*/
Node * hashMapGetKeyList(HashMap* hashMap)
{
   Node * data = hashMap->data;
   Node * head = NULL;
   int index = 0;
   while (index < hashMap->primeModulus)
   {
     Node * node = *((Node * *)((Node *)hashMap->data)+index);
     if (node != NULL)
     {
        while (node != NULL)
        {
          KeyValue * kv = node->data;
          if (head == NULL)
          {
            head = linkedListCreate(kv->key);
          }
          else
          {
            linkedListAdd(head, kv->key);
          }
          node = node->next;
        } 
     } 
     index++;
   }
  return head;
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

void hashMapRemove(HashMap* hashMap, char * key)
{
  Node * * head = hashMapGetHead(hashMap, key);
  if (*head != NULL)
  {
    *head = keyedListRemove(*head, key);
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
  while (node != NULL)
  {
    KeyValue * kv = node->data;
    if (kv != NULL)
    {
       if (kv->key != NULL && strcmp(kv->key, key) == 0)
	{
	  return (long *)kv->value;
	}
	node = node->next;
    } 
    else
    {
      return NULL;
    }
  }  
  return NULL;
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
