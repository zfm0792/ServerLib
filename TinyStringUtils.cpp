#include <cstring>
#include "TinyStringUtils.h"

bool isspace(char s);
void TinyStringUtils::trimLeft(char* string)
{
	char* p = string;
	//第一个字符不是空格
	if (!isspace(*p))
		return;
	
	//找到第一个不为空格的字符位置
	while (isspace(*p) && *p != '\0')
		p++;

	//全部都是空格
	if (*p == '\0')
		return;

	//return p;

	char* ret = string;
	
	while (*p != '\0')
	{
		*ret = *p;
		ret++;
		p++;
	}
	*ret = '\0';

	return;
}

void TinyStringUtils::trimRight(char* string)
{
	size_t len = 0;
	if (string == NULL)
		return;

	len = strlen(string);
	while (len > 0 && string[len - 1] == ' ')   //位置换一下   
		string[--len] = 0;
	return;
}

void TinyStringUtils::trim(char* string)
{
	trimLeft(string);
	trimRight(string);
}

bool isspace(char s)
{
	return s == ' ' || s == '\t' || s == '\r' || s == '\n';
}
