#include <multitasking/Process.h>

using namespace myos::common;

Process::Process()
{
    pid = -1;
    status = Ready;
    currentIndex = 0;
    topOfBufferIndex = 0;
    size = 0;
    ClearBuffer();
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

    cpustate->esp = (uint32_t)stack;
    cpustate->cs = cs;

    cpustate->eflags = 0x202;
}

bool Process::AddToBuffer(int8_t value)
{
    if (size == BUFF_SIZE)
        return false;

    stdbuff[topOfBufferIndex] = value;
    topOfBufferIndex = (topOfBufferIndex + 1) % BUFF_SIZE;
    ++size;
    
    return true;
}

int8_t Process::GetNextFromBuffer()
{
    if (size == 0)
        return 0;
        
    int8_t val = stdbuff[currentIndex];
    currentIndex = (currentIndex + 1) % BUFF_SIZE;
    --size;
    
    return val;
}

void Process::ClearBuffer()
{
    for (uint32_t i = 0 ; i < BUFF_SIZE ; ++i)
        stdbuff[i] = 0;
}

bool Process::IsBufferContainsNewlineChar()
{
    for (uint32_t i = currentIndex ; i <= topOfBufferIndex ; ++i)
        if (stdbuff[i] == '\n')
            return true;

    return false;
}

uint32_t Process::GetNextItemFromBuffer(int8_t* buffer, uint32_t count)
{
    uint32_t i = 0;
    int8_t tmpChr = 0;

    for (i = 0 ; i < count ;)
    {
        tmpChr = GetNextFromBuffer();

        if (tmpChr == '\n')
            break;
        
        if (tmpChr != 0)
            buffer[i++] = tmpChr;
    }

    if (i == count && stdbuff[currentIndex] == '\n')    // Skip \n character
        GetNextFromBuffer();

    return i;
}