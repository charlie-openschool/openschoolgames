
typedef struct HASHMAP
{
  long * data;
  int primeModulus;
} HashMap;

typedef struct NODE
{
  long * data;
  char * key;
  struct NODE * next;
}Node;

long stringHash(char * key, int primeModulus);
long * hashMapGet(HashMap* hashMap, char * key);

Node * createLinkedList(char * key, long * data);
Node * linkedListInsert(Node * node, char * key, long * data);
void linkedListRemove(Node * head, Node * node);
void linkedListRemoveByKey(Node * head, char * key);
Node * linkedListAdd(Node * head, char * key, long * data);
Node * linkedListGet(Node * head, char * key);
HashMap * hashMapCreate(int primeModulus);
void hashMapPut(HashMap* hashMap, char * key, long value);
long * hashMapGet(HashMap* hashMap, char * key);