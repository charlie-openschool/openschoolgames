#include <linkedlist.h>
#ifndef KEYED_LINKED_LIST
#define KEYED_LINKED_LIST
typedef struct KEY_VALUE
{
  void * value;
  char * key;
}KeyValue;


void * keyedListGet(Node * head, char * key);

Node * keyedListInsert(Node * node, char * key, void * data);

Node * keyedListCreate(char * key, void * value);

void keyedListRemove(Node * head, char * key);

Node * keyedListAdd(Node * head, char * key, void * value);

#endif