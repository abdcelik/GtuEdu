#ifndef _SYSCALL_HANDLER_H_
#define _SYSCALL_HANDLER_H_

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <multitasking/CPUState.h>
#include <multitasking/ProcessTable.h>
#include <lib/unixapi.h>

/*
    Handles software interrupts (syscalls)
*/
class SyscallHandler : public myos::hardwarecommunication::InterruptHandler
{
    public:
        SyscallHandler(myos::hardwarecommunication::InterruptManager* interruptManager, myos::common::uint8_t InterruptNumber);
        ~SyscallHandler();
        
        virtual myos::common::uint32_t HandleInterrupt(myos::common::uint32_t esp);

    private:
        void syscall_fork(CPUState* cpu);
        void syscall_waitpid(CPUState* cpu, uint32_t pid);
        void syscall_execve(CPUState* cpu);
        void syscall_exit(uint32_t status);
};

#endif