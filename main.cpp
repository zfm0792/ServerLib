#include <cstdio>
#include <unistd.h>
#include "TinyStringUtils.h"
#include "CConfigReader.h"
#include "global_func.h"

// ���ñ����йص�ȫ�ֱ���
char ** g_os_argv; // ��ʼ�������в��� ����  ��main�лᱻ��ֵ
char* gp_envmem = NULL; //ָ���Լ������env���������ڴ�
size_t g_environlen = 0; // ����������ռ�ڴ��С
int main(int argc,char* const* argv)
{
    g_os_argv = (char**)argv;
    init_setproctitle();// �ѻ����������
    setproctitle("nginx: master process");
    
    /*CConfigReader conf("/home/fredzhan/projects/ServerLib/test.conf");
    char* ServerPort = conf.getConfigName("ServerPort");
    char* a = conf.getConfigName("a");*/
    for (;;)
    {
        sleep(1);
        printf("sleep....\n");
    }
    return 0;
}