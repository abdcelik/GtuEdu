#include <multitasking/ProcessTable.h>
#include <lib/utility.h>

// Builds process table
// Our OS doesn't have dynamic memory. For this, I allocated some space in compile time
// Then I fill this entries with default values
ProcessTable::ProcessTable(GlobalDescriptorTable* gdt)
{
    current = -1;
    size = 0;

    for (uint32_t i = 0 ; i < PROCESS_TABLE_SIZE ; ++i)
        table[i].InitializeDefaultCpuState(gdt->CodeSegmentSelector());
}

ProcessTable::~ProcessTable() {}

uint32_t ProcessTable::GetCurrent()
{
    return current;
}

uint32_t ProcessTable::GetSize()
{
    uint32_t ret = 0;

    for (uint32_t i = 0 ; i < size ; ++i)
        if (table[i].status != Process::Terminated)
            ++ret;
    return ret;
}

Process::Status ProcessTable::GetStatus(uint32_t pid)
{
    return table[pid].status;
}

// Sets entry 0's instruction pointer as given entry point
// Sets process table size to 1 (only init process in process table)
void ProcessTable::CreateInitProcess(void (*entry_point)(void))
{
    Process* init = &table[0];

    init->pid = 0;
    init->cpustate->eip = (uint32_t)entry_point;
    size = 1;
}

// Creates (fills unused entry) child process
// Sets child instruction pointer with given ebx register (ebx register has an entry point)
pid_t ProcessTable::CreateProcessFrom(CPUState* cpustate)
{
    if (size >= PROCESS_TABLE_SIZE)
        return 0;

    Process* child = &table[size];

    child->cpustate->eip = cpustate->ebx;
    child->pid = size++;

    return child->pid;
}

void ProcessTable::TerminateProcess(uint32_t entry, uint32_t status)
{
    table[entry].status = Process::Terminated;
}

CPUState* ProcessTable::Schedule(CPUState* cpustate)
{
    if(size <= 0)
        return cpustate;

    if(current >= 0)
    {
        table[current].cpustate = cpustate;    // Store the old CPU state

        if (table[current].status == Process::Running)
            table[current].status = Process::Ready;
    }

    // -- Just printing screen (not related round robin scheduling) --
    int32_t printArr[3];
    printArr[0] = current;
    // ----

    do
    {
        if (++current >= size)
            current = 0;

    } while (table[current].status == Process::Terminated);

    table[current].status = Process::Running;

    // -- Just printing screen (not related round robin scheduling) --
    printArr[1] = current;
    if (printArr[0] == -1)
    {
        printArr[0] = printArr[1];
        printArr[1] = GetSize();
        print("---> Context switching: PID %d is on CPU. Process Table size: %d\n", 2, printArr);
    }
    else
    {
        printArr[2] = GetSize();
        print("---> Context switching: PID %d to PID %d. Process Table size: %d\n", 3, printArr);
    }
        
    // ----

    return table[current].cpustate;
}