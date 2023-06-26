#ifndef _UNIX_API_H_
#define _UNIX_API_H_

#include <common/types.h>
#include <multitasking/Process.h>

extern myos::common::uint32_t TIMERCOUNT;
extern myos::common::uint32_t DELAYCOUNT;

enum Syscall
{
    sys_exit = 1,
    sys_fork = 2,
    sys_read = 3,
    sys_waitpid = 7,
    sys_execve = 11
};

enum Exit
{
    exit_success = 0,
    exit_failure = 1
};

enum STD
{
    STDIN = 0,
    STDOUT = 1,
    STRERR = 2
};

// Makes fork systemcall
myos::common::pid_t fork();

// Makes waitpid systemcall
void waitpid(myos::common::pid_t pid);

// Makes execve systemcall
myos::common::int32_t execve(void (*entry_point)());

// Makes exit systemcall
void exit(Exit exit);

// Makes read systemcall
myos::common::ssize_t read(myos::common::int32_t fd, void* buf, myos::common::size_t count);

#endif