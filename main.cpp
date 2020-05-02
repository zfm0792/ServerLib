#include <cstdio>
#include <unistd.h>
#include "TinyStringUtils.h"
#include "CConfigReader.h"
#include "global_func.h"

// 设置标题有关的全局变量
char ** g_os_argv; // 初始的命令行参数 数组  在main中会被赋值
char* gp_envmem = NULL; //指向自己分配的env环境变量内存
size_t g_environlen = 0; // 环境变量所占内存大小
int main(int argc,char* const* argv)
{
    g_os_argv = (char**)argv;
    init_setproctitle();// 把环境变量搬家
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