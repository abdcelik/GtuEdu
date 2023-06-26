#ifndef _PROCESS_TABLE_H_
#define _PROCESS_TABLE_H_

#include <gdt.h>
#include <common/types.h>
#include <multitasking/CPUState.h>
#include <multitasking/Process.h>
#include <lib/utility.h>

#define PROCESS_TABLE_SIZE 256

using namespace myos;
using namespace myos::common;

class ProcessTable
{
    private:
        Process table[PROCESS_TABLE_SIZE];
        int32_t current;
        uint32_t size;
        
    public:
        // Builds process table
        ProcessTable(GlobalDescriptorTable* gdt);
        ~ProcessTable();

        // Returns current process index
        uint32_t GetCurrent();

        // Returns size of the table
        uint32_t GetSize();

        Process::Status GetStatus(uint32_t pid);

        // Creates init process and adds it to the process table
        void CreateInitProcess(void (*entry_point)(void));

        // Creates a new process using given cpu state and adds it to table
        pid_t CreateProcessFrom(CPUState* cpustate);

        void TerminateProcess(uint32_t entry, uint32_t status);

        CPUState* Schedule(CPUState* cpustate);
};

#endif