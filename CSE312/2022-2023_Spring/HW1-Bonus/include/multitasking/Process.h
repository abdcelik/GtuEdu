#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <common/types.h>
#include <multitasking/CPUState.h>

#define STACK_SIZE 4096 // 4 Kb
#define BUFF_SIZE 2048

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

        // Adds given value to the buffer
        bool AddToBuffer(myos::common::int8_t value);

        // Removes next byte from buffer
        myos::common::int8_t GetNextFromBuffer();

        // Fills whole buffer with 0
        void ClearBuffer();

        // Get next item from buffer and place it given buffer as given count
        myos::common::uint32_t GetNextItemFromBuffer(myos::common::int8_t* buffer, myos::common::uint32_t count);
        
        // Checks whether buffer is contains \n character or not
        bool IsBufferContainsNewlineChar();

    private:
        myos::common::uint8_t stack[STACK_SIZE];
        CPUState* cpustate;
        myos::common::uint32_t pid;
        Status status;

        myos::common::int8_t stdbuff[BUFF_SIZE];
        myos::common::uint16_t currentIndex;
        myos::common::uint16_t topOfBufferIndex;
        myos::common::uint16_t size;

        // Initializes cpu state with default value
        void InitializeDefaultCpuState(myos::common::uint16_t cs);
};

#endif