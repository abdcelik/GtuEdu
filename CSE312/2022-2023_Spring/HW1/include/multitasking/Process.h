#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <common/types.h>
#include <multitasking/CPUState.h>

#define STACK_SIZE 4096 // 4 Kb

using namespace myos::common;

class Process
{
    friend class ProcessTable;  // ProcessTable can access Process class fields
    
    public:
        enum Status
        {
            Running = 0,
            Ready = 1,
            Terminated = 2
        };

        Process();
        ~Process();

    private:
        uint8_t stack[STACK_SIZE];
        CPUState* cpustate;
        uint32_t pid;
        Status status;

        // Initializes cpu state with default value
        void InitializeDefaultCpuState(uint16_t cs);
};

#endif