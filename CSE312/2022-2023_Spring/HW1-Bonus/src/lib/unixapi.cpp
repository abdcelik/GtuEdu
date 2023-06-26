#include <lib/unixapi.h>

using namespace myos::common;

int32_t TMPVAL = -1;
Process::Status status;

pid_t fork()
{
    __asm__ volatile("int $0x80" : "=a" (TMPVAL) : "a" (sys_fork));
    return TMPVAL;
}

void waitpid(pid_t pid)
{
    status = Process::Running;

    while(status != Process::Terminated)
        __asm__ volatile("int $0x80" : "=a" (status) : "a" (sys_waitpid), "b" (pid));
}

int32_t execve(void (*entry_point)())
{
    __asm__ volatile("int $0x80" : : "a" (sys_execve), "b" (entry_point));
    return TMPVAL;
}

void exit(Exit exit)
{
    __asm__ volatile("int $0x80" : : "a" (sys_exit));
    while(true);
}

ssize_t read(int32_t fd, void* buf, size_t count)
{
    int32_t size = 0;

    while(size == 0)
    {
        if (TIMERCOUNT >= DELAYCOUNT)
        {
            TIMERCOUNT = 0;
            __asm__ volatile("int $0x80" : "=a" (size) : "a" (sys_read), "b" (fd), "c" (buf), "d" (count));
        }
    }

    return size;
}