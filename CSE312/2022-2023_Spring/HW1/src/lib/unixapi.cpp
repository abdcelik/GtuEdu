#include <lib/unixapi.h>

pid_t fork(void (*entry_point)(void))
{
    uint32_t ret = -1;

    __asm__ volatile("movl %0, %%eax; movl %1, %%ebx; int $0x80;" :
                 : "r" (sys_fork), "r" (entry_point) : "eax", "ebx");
    __asm__ volatile("" : "=a"(ret));

    return ret;
}

void waitpid(uint32_t pid)
{
    Process::Status ret = Process::Running;

    while(ret != Process::Terminated)
    {
        __asm__ volatile("movl %0, %%eax; movl %1, %%ebx; int $0x80;" :
                 : "r" (sys_waitpid), "r" (pid) : "eax", "ebx");
        __asm__ volatile("" : "=a"(ret));
    }
}

void execve()
{
    // TO DO
}

void exit(Exit exit)
{
    __asm__ volatile("movl %0, %%eax; movl %1, %%ebx; int $0x80;" :
                 : "r" (sys_exit), "r" (exit) : "eax", "ebx");
    
    while(true);
}