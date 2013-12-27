#include <strings.h>
#include <testasserts.h>
#include <stdlib.h>
#include <constants.h>
#include <stdio.h>

/*
* Tests
*/

void testSplit()
{ 
  char ** words = split("hello,world,goodbye",',');
  assertStrEquals("testSplit word one", "hello", words[0]);
  assertStrEquals("testSplit word two", "world", words[1]);
  assertStrEquals("testSplit word three", "goodbye", words[2]);
  free(words[0]);
  free(words[1]);
  free(words[2]);
  free(words);
}

void testSplitOneWord()
{ 
  char ** words = split("hello",',');
  assertStrEquals("testSplitOneWord", "hello", words[0]);
  free(words[0]);
  free(words);
}

void testSplitNull()
{ 
  char ** words = split(NULL,',');
  free(words);
}

void testLengthNull()
{
  char * s = NULL;
  int len = length(s);
  assertIntEquals("testLengthNull", 0, len);
}

void testLength()
{
  char * s = "Hello World";
  int len = length(s);
  assertIntEquals("testLength", 11, len);
}


void testReverse()
{
  char * greeting = "Hello World";
  char * reverseGreeting = "dlroW olleH";
  char * result = reverse(greeting);
  assertStrEquals("testReverse", reverseGreeting, result);
  assertStrEquals("testReverse data integrity", greeting, "Hello World");
}

void testStringEquals()
{
  char * str1 = "a";
  char * str2 = "a";
  int r = stringEquals(str1, str2);
  assertIntEquals("testStringEquals", r, TRUE);
}

void testStringEqualsNulls()
{
  char * str1 = 0;;
  char * str2 = 0;
  int r = stringEquals(str1, str2);
  assertIntEquals("testStringEqualsNulls", r, TRUE);
}

void testClone()
{
  char * greeting = "Hello World";
  char * clonedGreeting = "Hello World";
  char * result = clone(greeting);
 
  assertStrEquals("testClone", clonedGreeting, result);
  assertStrEquals("testClone data integrity", greeting, "Hello World");
}

void testToUpper()
{
  char * str = "abc defg";
  char * expected = "ABC DEFG";
  char * result = toUpper(str);
  assertStrEquals("testToUpper", expected, result);
}

void testToLower()
{
  char * str = "ABc deFg";
  char * expected = "abc defg";
  char * result = toLower(str);
  assertStrEquals("testToLower", expected, result);
}

void testStringEqualsNoCase()
{
  char * str1 = "aBc dEfG";
  char * str2 = "AbC DeFg";
  assertIntEquals("testStringEqualsNoCase", TRUE, stringEqualsNoCase(str1, str2));
  assertStrEquals("testStringEqualsNoCase data integrity 1", "aBc dEfG", str1);
  assertStrEquals("testStringEqualsNoCase data integrity 2", "AbC DeFg", str2);
}

void testStringConcat()
{
  char * s1 = "hello";
  char * s2 = "world";
  char * result = stringConcat(s1, s2);
  assertStrEquals("testStringConcat", "helloworld", result);
}

void testEchoStrings()
{
  echoStrings("Hello World!");
}

int main()
{
  int numberOfTests = 13;
  void (*tests[numberOfTests])(void);
  tests[0] = testReverse;
  tests[1] = testClone;
  tests[2] = testToUpper;
  tests[3] = testToLower;
  tests[4] = testStringEqualsNoCase;
  tests[5] = testStringEqualsNulls;
  tests[6] = testLength;
  tests[7] = testLengthNull;
  tests[8] = testStringConcat;
  tests[9] = testEchoStrings;
  tests[10]= testSplit;
  tests[11]= testSplitOneWord;
  tests[12]= testSplitNull;
  int i = 0;
  while (i < numberOfTests)
  {
    tests[i]();
	printf("\n");
	i++;
  }

  printf("%d asserts successful.\n", assertsGetTotal());
  if (assertsGetFailures() > 0)
  {
    printf("%d asserts failed.\n", assertsGetFailures());
  }
  else
  {
    printf("All tests successful.\n");
  }

return 0;
}