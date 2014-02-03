#include <stdlib.h>
#include <stdio.h>
#include <linkedlist.h>

Node * linkedListCreate(void * data)
{
   Node * head = malloc(sizeof( Node));
   head->data = data;
   head->next = NULL;
   return head; 
}

Node * linkedListRemove(Node * head, Node * node)
{
  Node * current = head;
  Node * previous = head;
  if (head == node)
  {
    if (head->next != NULL)
	{
	  Node * t = head->next;
	  head->data = t->data;
	  head->next = t->next;
	  free(t);
	  t = NULL;
	}
  }
  else 
  {
    while (current != NULL && current != node)
    {
      previous = current;
      current = current->next;
    }
    if (current != NULL)
    {
      previous->next = current->next;
      free(current);
      current = NULL; 
    }
  }
  return previous;
}

void linkedListInsert(Node * current, void * data)
{
  Node * node = linkedListCreate(data);
  node->next = current->next;
  current->next = node;
}

Node * linkedListAdd(Node * head, void * data)
{
  while (head->next != NULL)
  {
     head = head->next;    
  }
  linkedListInsert(head, data);
  return head->next;
}

