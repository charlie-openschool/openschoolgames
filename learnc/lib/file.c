#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define CNTL_Z '\032'

void printChar(char ch);

char * fileRead(char * fileName)
{  
  FILE *fp = NULL;
  long count = 0;
  long size = 0;;
  char * s = NULL;  
  if ((fp = fopen(fileName, "r")) == NULL)
  {
    printf("cannot open %s \n", fileName);
	return NULL;
  }
  
  fseek(fp, 0L, SEEK_END);
  size = ftell(fp);
  s = malloc(sizeof(char)*(size +1));
  char * t = s;
  for (count = 0L; count < size; count++)
  {
	fseek(fp, count, SEEK_SET);
	char ch = getc(fp);
    *t = ch;
	t++;
  }
  *t = '\0';
  
/*  for (count = 0L; count <= last; count++)
  {
	fseek(fp, -count, SEEK_END);
	ch = getc(fp);
    printChar(ch);
  }
*/  
  fclose(fp);
  return s;
}

void fileWrite(char * fileName, char * msg)
{  
  FILE *fp = NULL;
  long count = 0;
  long size = 0;;
  char * s = NULL;  
  if ((fp = fopen(fileName, "w")) == NULL)
  {
    printf("cannot open %s \n", fileName);
	return;
  }
  
  size = strlen(msg);
  char * t = msg;
  for (count = 0L; count < size; count++)
  {
	fseek(fp, count, SEEK_SET);
	putc(*t, fp);
	t++;
  }
  fclose(fp);
  return;
  }
  
void printChar(char ch)
{
  if (ch != CNTL_Z && ch != '\r')
  {
    putchar(ch);
  }
}