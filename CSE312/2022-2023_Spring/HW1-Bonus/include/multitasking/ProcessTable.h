#ifndef _PROCESS_TABLE_H_
#define _PROCESS_TABLE_H_

#include <common/types.h>
#include <gdt.h>
#include <lib/utility.h>
#include <multitasking/CPUState.h>
#include <multitasking/Process.h>

#define PROCESS_TABLE_SIZE 256

class ProcessTable
{
    private:
        Process table[PROCESS_TABLE_SIZE];
        myos::common::int32_t current;
        myos::common::uint32_t size;
        
    public:
        // Builds process table
        ProcessTable(myos::GlobalDescriptorTable* gdt);

        ~ProcessTable();

        // Sets current process instruction pointer (eip) to given eip
        bool SetCurrentProcessInstructionPoint(myos::common::uint32_t eip);

        // Returns current process index
        myos::common::uint32_t GetCurrent();

        // Returns size of the table
        myos::common::uint32_t GetSize();

        Process::Status GetStatus(myos::common::uint32_t pid);

        // Creates init process and adds it to the process table
        void CreateInitProcess(void (*entry_point)(void));

        // Creates a new process using given cpu state and adds it to table
        myos::common::pid_t CreateProcessFrom(CPUState* cpustate);

        // Makes process status terminated in the given entry
        void TerminateProcess(myos::common::uint32_t entry);

        // Manage process table and makes scheduling (context switching)
        CPUState* Schedule(CPUState* cpustate);

        // Adds given value to buffer of process running on the CPU
        bool AddCurrentProcessBuffer(myos::common::int8_t value);

        // Gets value from process running on the CPU
        myos::common::int8_t GetCurrentProcessBuffer();

        // Checks whether process running on the CPU is contains item or not
        bool CurrentProcessBufferContainsItem();

        // Reads the given count bytes from the buffer
        // If there are \n characters in the buffer before count byte, it reads up to \n bytes
        // Returns the number of filled bytes
        myos::common::uint32_t GetNextItemFromCurrentProcess(myos::common::int8_t* buffer, myos::common::uint32_t count);
};

#endif