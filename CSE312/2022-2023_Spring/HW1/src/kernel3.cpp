#include <common/types.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <syscalls/syscallhandler.h>
#include <lib/utility.h>
#include <multitasking/ProcessTable.h>

using namespace myos;
using namespace myos::common;
using namespace myos::hardwarecommunication;

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

uint32_t random_seed = 123456;

void initProcess();
void binarySearch();
void linearSearch();
void collatz();
uint32_t rand();

extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    GlobalDescriptorTable gdt;
    ProcessTable processTable(&gdt);
    InterruptManager interrupts(0x20, &gdt, &processTable);
    SyscallHandler syscalls(&interrupts, 0x80);

    processTable.CreateInitProcess(initProcess);
    interrupts.Activate();
    
    while(true);    // kernelMain is going ghost mode
}

void initProcess()
{
    printf("Init: Started...\n");
    const uint32_t numOfProcess = 6;
    pid_t pids[numOfProcess];
    void (*process[])() = {binarySearch, linearSearch, collatz};
    uint32_t random[] = {rand() % 3, rand() % 3};
    
    printf("Init: Forking is started...\n");
    for (uint32_t i = 0 ; i < numOfProcess ; ++i)
        pids[i] = fork(process[random[i % 2]]);
    printf("Init: Forking is finished...\n");

    printf("Init: Waiting child to terminate...\n");
    for (uint32_t i = 0 ; i < numOfProcess ; ++i)
        waitpid(pids[i]);
    printf("Init: All child finished and collected. Init is exiting...");

    exit(exit_success);
}

void binarySearch()
{
    uint32_t arr[] =  {10, 20, 80, 30, 60, 50, 110, 100, 130, 170};
    uint32_t low = 0, mid = 0, high = 9;
    uint32_t key = 110, index = -1;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (arr[mid] == key)
        {
            index = mid;
            break;
        }
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    
    int32_t printArr[] = {index};
    print("Binary search result: %d\n", 1, printArr);

    exit(exit_success);
}

void linearSearch()
{
    uint32_t arr[] = {10, 20, 80, 30, 60, 50, 110, 100, 130, 170};
    uint32_t size = 10;
    uint32_t key = 175, index = -1;

    for (uint32_t i = 0 ; i < size ; ++i)
        if (arr[i] == key)
        {
            index = i;
            break;
        }
    
    int32_t printArr[] = {index};
    print("Linear search result: %d\n", 1, printArr);
    
    exit(exit_success);
}

void collatz()
{
    int32_t printArr[1];

    for (uint32_t i = 20 ; i < 25 ; ++i)
    {
        printArr[0] = i;
        print("Collatz %d: ", 1, printArr);
        uint32_t key = i;

        while (key != 1)
        {
            printArr[0] = key;
            print("%d, ", 1, printArr);

            if (key % 2 == 0)
                key /= 2;
            else
                key = key * 3 + 1;
        }

        printArr[0] = 1;
        print("%d\n", 1, printArr);
    }

    exit(exit_success);
}

uint32_t rand()
{
    random_seed = random_seed * 1103515245 + 12345;
    return random_seed;
}