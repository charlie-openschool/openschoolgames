#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <testasserts.h>
#include <constants.h>
#include <strings.h>
#include <time.h>
#include <stdlib.h>

int randomInitialized = 0;
char * getRandomString(int length)
{
   if (randomInitialized < 1)
   {
     srand(time(NULL));
	 randomInitialized = 1;
   }
   int i = 0;
   char * s = (char *)malloc(sizeof(char) * length);
   char * p = s;
   while (i < (length - 1))
   {
     i++;
     int cap = rand()%2;
     int offset = rand()%25;
	 if (cap > 0)
	 {
	   *p = 'a' + offset; 
	 }
	 else
	 {
	   *p = 'A' + offset;
	 }
	 p++;
  }
  *p = '\0';
    
  return s;
}

/**
 * length not including null terminator 
 * example: char [] s = {'h','e','l','l','o','\0'};
 * int len = length(s);
 * len == 5
 */
int length(char * s)
{
  int i = 0;
  while (s != 0 && s[i] != 0)
  {
    i++;
  }
  return i;
}
/**
 * length including null terminator
*/
int rawLength(char * s)
{
  return length(s) + 1;
}
/**
 * allocate new memory and fill with the reverse of s
 */
char * reverse(char * s)
{
  char * t = clone(s);
  int i = length(s);
  int j = 0;
  i -= 1; // start with the character before the null terminator
  
  while (i >= 0)
  {
    t[j] = s[i];
	i--;
	j++;
  }
  
  t[j] = 0; // null terminate after the last character
  return t;
}

char * convertString(char * s, int offset)
{
  char * t;
  int len = rawLength(s);
  int i = 0;
  t = (char*)malloc(sizeof(char) * len);
  while (i < len)
  {
    if ((s[i] <= 'z' && s[i] >= 'a') && offset < 0)
	{
	  t[i] = s[i] + offset;
	}
	else if ((s[i] <= 'Z' && s[i] >= 'A') && offset > 0)
	{
	  t[i] = s[i] + offset;
	}
	else
	{
	  t[i] = s[i];
	}
	i++;
  }
  
  return t;
}

void ascii()
{
  int i = 0;
  while (i < 256)
  {
    printf("%d: %c\n", i, i);
	i++;
  }
}

char * toLower(char * s)
{
  return convertString(s, 32);
}

char * toUpper(char * s)
{
  return convertString(s, -32);
}

char * clone(char * s)
{
  int i = length(s);
  i++;
  char * t = (char*)malloc(sizeof(char) * i);
  strcpy(t, s);
  return t;
}

void inspect(char * s, int len)
{
  printf("**********************\n");
  printf("\n");
  printf("s: %s\n", s);
  printf("len: %d\n", strlen(s));
  printf("size: %d\n", sizeof(s));
  int i = 0;
  while (i < len)
  {
    printf(":%d ", s[i]);
	i++;
  }
  printf("\n");
  i = 0;
  while (i < len)
  {
    printf(":%c ", s[i]);
	i++;
  }
  printf("\n");
  printf("**********************\n");
}
/**
  * compare two strings return
  * TRUE if strings are character by character equal
  * FALSE otherwise
*/
int stringEquals(char * s1, char * s2)
{
  int len1 = length(s1);
  int len2 = length(s2);
  int equal = FALSE;
  if (len1 == len2)
  {
    equal = TRUE;
    int i = 0;
	while (i < len1)
	{
	  if (s1[i] != s2[i])
	  {
	    equal = FALSE;
		break;
	  }
	  i++;
	}
  }
  return equal;
}

int stringEqualsNoCase(char * s1, char * s2)
{
  int len1 = length(s1);
  int len2 = length(s2);
  char * t1;
  char * t2;
  int equal = FALSE;
  if (len1 == len2)
  {
    t1 = toUpper(s1);
	t2 = toUpper(s2);
    equal = TRUE;
    int i = 0;
	while (i < len1)
	{
	  if (t1[i] != t2[i])
	  {
	    equal = FALSE;
		break;
	  }
	  i++;
	}
  }
  return equal;
}
/**
* Return a new strings from s1 + s2
* Example stringConcat("hello", "world");
* returns: helloworld
*/
char * stringConcat(char * s1, char * s2)
{
  int len1 = length(s1);
  int len = len1 + length(s2);
  len++;
  char * result = (char *)malloc(sizeof(char) * len);
  strcpy(result, s1);
  char * mid = result + len1;
  strcpy(mid, s2);
  return result;
}

/**
* Demonstrate advancing a pointer to move along a string of characters.
*/
void echoStrings(char * s)
{
  int len = length(s);
  int i = 0;
  while (i < len)
  {
    printf("%s\n", s);
	i++;
	s++;
  }
}

char ** split(char * s, char delimiter)
{
  int len = length(s);
  int cnt = 0;
  int i = 0;
  while (i < len)
  {
    if (s[i] == delimiter)
	{
	  cnt++;
	}
	i++;
  }
  char ** words = (char**)malloc(sizeof(char*)*(cnt+1));
  i = 0;
  cnt = 0;
  while (i < len)
  {
    int wordLen = 0;
    char * wordStart = s + i;
    while(s[i] != delimiter)
	{
	  wordLen++;
	  i++;
	}
	i++;
	char * word = (char *)malloc(sizeof(char)*(wordLen + 1));
	strncpy(word, wordStart, wordLen);
	word[wordLen] = '\0';
    words[cnt] = word;
	cnt++;
  }
  return words;
}