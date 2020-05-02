
#include <unistd.h> // env
#include <string.h>
#include "global_func.h"
//���ÿ�ִ�г��������صĺ���  �����ڴ�  ���Ұѻ�������copy�����ڴ���
void init_setproctitle()
{
	int i;
	for (i = 0; environ[i]; i++)
	{
		//�õ��ܵ�env����  +1 'xxxx\0'
		g_environlen += strlen(environ[i]) + 1;
	}

	// ���ж�gp_envmem == NULL  ����Ϊ����ڴ˴�newʧ���� ���޷�����  ֱ���ó����������
	// һ����� ����ֵΪNULL ���� �׳��쳣
	gp_envmem = new char[g_environlen];
	memset(gp_envmem, 0, g_environlen); // �ڴ����   ��ֹ��������

	char* ptmp = gp_envmem;

	// ��ԭ�����ڴ�copy�����ڴ�
	for (i = 0; environ[i]; i++)
	{
		//strlen  �������ַ�'\0'
		size_t size = strlen(environ[i]) + 1;
		//memcpy(ptmp,environ[i],size);
		strcpy(ptmp, environ[i]); // ��ԭ�ڴ����ݿ��������ڴ�
		environ[i] = ptmp; // ���»�������ָ��������ڴ�
		ptmp += size;
	}
	return;
}

// ���ÿ�ִ�г������
void setproctitle(const char* title)
{
	//������ⳤ��
	size_t titlelen = strlen(title);

	//����ԭʼ��argv �ڴ��ܳ���
	size_t e_environlen = 0;
	for (int i = 0;g_os_argv[i]; i++)
	{
		e_environlen += strlen(g_os_argv[i]) + 1;
	}
	//������������ñ����ڴ���ܺ�
	size_t esy = e_environlen + g_environlen;
	if (esy <= titlelen) // ����ĳ���̫�� �����ڴ����  ��ֱ��return
	{
		return;
	}
	//���ⳤ���㹻
	// ���ú����������в���Ϊnull ����argv[] ��ֻ��һ��Ԫ��   ��ֹ����argv������
	g_os_argv[1] = NULL;

	//������copy ��ȥ
	char* ptmp = g_os_argv[0];
	strcpy(ptmp, title);
	ptmp += titlelen;

	//��ʣ���ԭargv�Լ�environ��ռ���ڴ�ȫ����0������������ps��cmd�п��ܻ������һЩû�б����ǵ����ݣ�
	size_t cha = esy - titlelen;
	memset(ptmp, 0, cha);
	return;
}
