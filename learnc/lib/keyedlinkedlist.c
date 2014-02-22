#include <keyedlinkedlist.h>
#include <linkedlist.h>
#include <stdlib.h>
#include <stdio.h>

void * keyedListGet(Node * head, char * key)
{
  Node * current = head;
  while (current != 0)
  {
    KeyValue * kv = current->data;
    if (strcmp(kv->key, key) == 0)
	{
	  return current->data;
	}
    current = current->next;
  }
  return 0;
}

Node * keyedListGetNode(Node * head, char * key)
{
  Node * current = head;
  while (current != 0)
  {
    KeyValue * kv = current->data;
    if (strcmp(kv->key, key) == 0)
	{
	  return current;
	}
    current = current->next;
  }
  return 0;
}

Node * keyedListInsert(Node * node, char * key, void * data)
{
  Node * insertedNode = keyedListCreate(key, data);
  Node * next = node->next;
  node->next = insertedNode;
  insertedNode->next = next;
  return insertedNode;
}

Node * keyedListCreate(char * key, void * value)
{
  KeyValue * kv = malloc(sizeof(KeyValue));
  kv->key = key;
  kv->value = value;
  return linkedListCreate(kv);
}

void keyedListRemove(Node * head, char * key)
{
  Node * current = keyedListGetNode(head, key);
  if (current != NULL)
  {
    KeyValue * kv = current->data;
    free(kv);
    linkedListRemove(head, current);
  }
}

Node * keyedListAdd(Node * head, char * key, void * value)
{
  KeyValue * kv = malloc(sizeof(KeyValue));
  kv->key = key;
  kv->value = value;
  return linkedListAdd(head, kv);
}