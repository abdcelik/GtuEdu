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
            syscall_waitpid(cpu);
            break;
        case sys_execve:
            syscall_execve(cpu);
            break;
        case sys_exit:
            syscall_exit();
            break;
        case sys_read:
            syscall_read(cpu);
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

void SyscallHandler::syscall_waitpid(CPUState* cpu)
{
    cpu->eax = interruptManager->tableManager->GetStatus(cpu->ebx);
}

void SyscallHandler::syscall_execve(CPUState* cpu)
{
    cpu->eax = interruptManager->tableManager->SetCurrentProcessInstructionPoint(cpu->ebx) == true ? 0 : -1;
}

void SyscallHandler::syscall_exit()
{
    interruptManager->tableManager->TerminateProcess(interruptManager->tableManager->GetCurrent());
}

void SyscallHandler::syscall_read(CPUState* cpu)
{
    if (cpu->ebx != STDIN || !interruptManager->tableManager->CurrentProcessBufferContainsItem())
    {
        cpu->eax = 0;
        return;
    }

    cpu->eax = interruptManager->tableManager->GetNextItemFromCurrentProcess((int8_t*)cpu->ecx, cpu->edx);
}