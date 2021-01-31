#ifndef STRING_H
#define STRING_H
 
#include <malloc.h>
#include <stdio.h>
#include <conio.h>

#define FALSE 0
#define TRUE 1
int StrLen(char* str)
{
	int i;
	for (i = 0; *(str+i) != '\0' ; i++);
	return i;
}

char* CopyStringToHeap(char* inStackString)
{
	int len = StrLen(inStackString);
	char* ret = (char*)malloc(len + 1);
	for (int i = 0; i < len; i++)
		ret[i] = inStackString[i];
	ret[len] = '\0';
	return ret;
}

int CompareStrings(char* str1, char* str2)
{
	int len1 = StrLen(str1);
	if (len1 != StrLen(str2))
		return FALSE;

	for (int i = 0; i < len1; i++)
		if (str1[i] != str2[i])
			return FALSE;
	
	return TRUE;
}

char* GetStringInput()
{
	char* buffer = (char*)malloc(1000000); //Allocate 1Mb memory
	int i = 0;
	char ch = 0;
	while ((ch = _getch()) != '\r')
	{
		buffer[i++] = ch;
		putchar(ch);
	}
	buffer[i] = '\0';
	char* input = (char*)malloc(i + 1);
	memcpy(input, buffer, i + 1);
	free(buffer);
	putchar('\n');
	return input;
}
#endif // !STRING_H
