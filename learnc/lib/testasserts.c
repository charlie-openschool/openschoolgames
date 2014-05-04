#include <testasserts.h>
#include <constants.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <file.h>

int totalAsserts = 0;
int failures = 0;

int assertsGetTotal()
{
  return totalAsserts;
}

int assertsGetFailures()
{
  return failures;
}

/**
  * compare two strings return
  * TRUE if strings are character by character equal
  * FALSE otherwise
*/
int localStringEquals(char * s1, char * s2)
{
  int len1 = strlen(s1);
  int len2 = strlen(s2);
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

void assertStrEquals(char * message, char * expected, char * actual)
{
  totalAsserts++;
  if (localStringEquals(expected, actual) != TRUE)
  {
    failures++;
    printf("%s FAILED \nexpected: %s \nactual: %s\n", message, expected, actual);
  }
  else
  {
    printf("%s SUCCESS\n", message);
  }
}

void assertIntEquals(char * message, int expected, int actual)
{
  totalAsserts++;
  if (expected != actual)
  {
    failures++;
    printf("%s FAILED \nexpected: %d \nactual: %d\n", message, expected, actual);
  }
  else
  {
    printf("%s SUCCESS\n", message);
  }
}

void assertWriteResults(char * testName)
{
  char * results = fileRead("test_results");
  char * endResults = NULL;
  printf("%d asserts successful.\n", assertsGetTotal());
  char * str = malloc(sizeof(char) * 50);
  if (assertsGetFailures() > 0)
  {
    printf("%d asserts failed.\n", assertsGetFailures());
	sprintf(str, "Test: %s %d asserts failed.\n", testName, assertsGetFailures());
	endResults = stringConcat(results, str);
    free(str);	
  }
  else
  {
    printf("All tests successful.\n");
	sprintf(str, "Test: %s  successful.\n", testName);
	endResults = stringConcat(results, str);
  }
  fileWrite("test_results", endResults);
  free(str);
  free(results);
  free(endResults);
}