#ifndef _UNIX_API_H_
#define _UNIX_API_H_

#include <common/types.h>
#include <lib/utility.h>
#include <multitasking/Process.h>

using namespace myos::common;

enum Syscall
{
    sys_exit = 1,
    sys_fork = 2,
    sys_waitpid = 7,
    sys_execve = 11
};

enum Exit
{
    exit_success = 0,
    exit_failute = 1
};

// Makes fork systemcall
pid_t fork(void (*entry_point)(void));

// Makes waitpid systemcall
void waitpid(uint32_t pid);

// Makes execve systemcall
void execve();

// Makes exit systemcall
void exit(Exit exit);

#endif