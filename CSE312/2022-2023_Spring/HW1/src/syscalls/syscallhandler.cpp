#include <syscalls/syscallhandler.h>

using namespace myos;
using namespace myos::common;
using namespace myos::hardwarecommunication;

SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8_t InterruptNumber)
    : InterruptHandler(interruptManager, InterruptNumber  + interruptManager->HardwareInterruptOffset()) {}

SyscallHandler::~SyscallHandler() {}

uint32_t SyscallHandler::HandleInterrupt(uint32_t esp)
{
    CPUState* cpu = (CPUState*)esp;

    switch(cpu->eax)
    {
        case sys_fork:
            syscall_fork(cpu);
            break;
        case sys_waitpid:
            syscall_waitpid(cpu, cpu->ebx);
            break;
        case sys_execve:
            syscall_execve(cpu);
            break;
        case sys_exit:
            syscall_exit(cpu->ebx);
            break;
        default:
            break;
    }

    return esp;
}

void SyscallHandler::syscall_fork(CPUState* cpu)
{
    cpu->eax = interruptManager->tableManager->CreateProcessFrom(cpu);
}

void SyscallHandler::syscall_waitpid(CPUState* cpu, uint32_t pid)
{
    cpu->eax = interruptManager->tableManager->GetStatus(pid);
}

void SyscallHandler::syscall_execve(CPUState* cpu)
{
    // TO DO
}

void SyscallHandler::syscall_exit(uint32_t status)
{
    interruptManager->tableManager->TerminateProcess(interruptManager->tableManager->GetCurrent(), status);
}