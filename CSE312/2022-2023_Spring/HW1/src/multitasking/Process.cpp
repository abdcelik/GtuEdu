#include <multitasking/Process.h>

Process::Process()
{
    pid = -1;
    status = Ready;
}

Process::~Process() {}

void Process::InitializeDefaultCpuState(uint16_t cs)
{
    cpustate = (CPUState*)(stack + STACK_SIZE - sizeof(CPUState));
    
    cpustate->eax = 0;
    cpustate->ebx = 0;
    cpustate->ecx = 0;
    cpustate->edx = 0;

    cpustate->esi = 0;
    cpustate->edi = 0;
    cpustate->ebp = 0;
    
    cpustate->error = 0;    

    cpustate->esp = (uint32_t)cpustate;
    cpustate->cs = cs;

    cpustate->eflags = 0x202;
}