#include <cstring>
#include "TinyStringUtils.h"

bool isspace(char s);
void TinyStringUtils::trimLeft(char* string)
{
	char* p = string;
	//��һ���ַ����ǿո�
	if (!isspace(*p))
		return;
	
	//�ҵ���һ����Ϊ�ո���ַ�λ��
	while (isspace(*p) && *p != '\0')
		p++;

	//ȫ�����ǿո�
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
	while (len > 0 && string[len - 1] == ' ')   //λ�û�һ��   
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
