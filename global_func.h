#ifndef __GLOBAL_FUNC_H__
#define __GLOBAL_FUNC_H

extern char** g_os_argv; // ��ʼ�������в��� ����  ��main�лᱻ��ֵ
extern char* gp_envmem;
extern size_t g_environlen;

void init_setproctitle();
void setproctitle(const char* title);

#endif // !__GLOBAL_FUNC_H__
