
#include <unistd.h> // env
#include <string.h>
#include "global_func.h"
//设置可执行程序标题相关的函数  分配内存  并且把环境变量copy到新内存中
void init_setproctitle()
{
	int i;
	for (i = 0; environ[i]; i++)
	{
		//得到总的env长度  +1 'xxxx\0'
		g_environlen += strlen(environ[i]) + 1;
	}

	// 不判断gp_envmem == NULL  是因为如果在此处new失败了 将无法处理  直接让程序崩溃更好
	// 一般情况 返回值为NULL 或者 抛出异常
	gp_envmem = new char[g_environlen];
	memset(gp_envmem, 0, g_environlen); // 内存清空   防止出现问题

	char* ptmp = gp_envmem;

	// 将原来的内存copy到新内存
	for (i = 0; environ[i]; i++)
	{
		//strlen  不包含字符'\0'
		size_t size = strlen(environ[i]) + 1;
		//memcpy(ptmp,environ[i],size);
		strcpy(ptmp, environ[i]); // 将原内存内容拷贝到新内存
		environ[i] = ptmp; // 让新环境变量指向这段新内存
		ptmp += size;
	}
	return;
}

// 设置可执行程序标题
void setproctitle(const char* title)
{
	//计算标题长度
	size_t titlelen = strlen(title);

	//计算原始的argv 内存总长度
	size_t e_environlen = 0;
	for (int i = 0;g_os_argv[i]; i++)
	{
		e_environlen += strlen(g_os_argv[i]) + 1;
	}
	//计算可用于设置标题内存的总和
	size_t esy = e_environlen + g_environlen;
	if (esy <= titlelen) // 标题的长度太长 导致内存溢出  故直接return
	{
		return;
	}
	//标题长度足够
	// 设置后续的命令行参数为null 这样argv[] 中只有一个元素   防止后续argv被滥用
	g_os_argv[1] = NULL;

	//将标题copy 进去
	char* ptmp = g_os_argv[0];
	strcpy(ptmp, title);
	ptmp += titlelen;

	//把剩余的原argv以及environ所占的内存全部清0，否则会出现在ps的cmd列可能还会残余一些没有被覆盖的内容；
	size_t cha = esy - titlelen;
	memset(ptmp, 0, cha);
	return;
}
