#include <common/types.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/pci.h>
#include <syscalls/syscallhandler.h>
#include <lib/utility.h>
#include <multitasking/ProcessTable.h>

using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

void initProcess();
void binarySearch();
void linearSearch();
void collatz();

void (*process[])() = {binarySearch, linearSearch, collatz};
uint32_t RANDOM_NUM1, RANDOM_NUM2;

extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/)
{
    GlobalDescriptorTable gdt;
    ProcessTable processTable(&gdt);
    InterruptManager interrupts(0x20, &gdt, &processTable);
    SyscallHandler syscalls(&interrupts, 0x80);

    processTable.CreateInitProcess(initProcess);

    DriverManager driverManager;
    MouseDriver mouse(&interrupts);

    PrintfKeyboardEventHandler kbhandler;
    KeyboardDriver keyboard(&interrupts, &kbhandler);

    driverManager.AddDriver(&keyboard);
    driverManager.AddDriver(&mouse);
    driverManager.ActivateAll();
    
    interrupts.Activate();
    
    while(true);    // kernelMain is going ghost mode
}

void initProcess()
{
    printf("Init: Started...\n");

    const uint32_t numOfProcess = 6;
    const uint32_t numOfProgram = 3;
    pid_t pids[numOfProcess];

    RANDOM_NUM1 = rand() % numOfProgram;
    RANDOM_NUM2 = (RANDOM_NUM1 + 1) % numOfProgram;
    
    printf("Init: Forking is started...\n");

    for (uint32_t i = 0 ; i < numOfProcess / 2 ; ++i)
        if ((pids[i] = fork()) == 0)    // child continues
        {
            execve(process[RANDOM_NUM1]);
            exit(exit_failure);
        }

    for (uint32_t i = numOfProcess / 2  ; i < numOfProcess ; ++i)
        if ((pids[i] = fork()) == 0)    // child continues
        {
            execve(process[RANDOM_NUM2]);
            exit(exit_failure);
        }

    // parent continues
        
    printf("Init: Forking is finished...\n");
    printf("Init: Waiting child to terminate...\n");

    for (uint32_t i = 0 ; i < numOfProcess ; ++i)
        waitpid(pids[i]);

    printf("Init: All child finished and collected. Init terminated...");
    exit(exit_success);
}

void binarySearch()
{
    printf("Binary Search: Started...\n");

    const uint32_t ARRSIZE = 16;
    uint32_t arr[ARRSIZE];
    uint32_t arraySize = 0;
    uint32_t low = 0, mid = 0, high = 0;
    uint32_t key = 0, index = -1;
    
    arraySize = readUint32_t("BS: Enter size of array: ");

    for (uint32_t i = 0 ; i < arraySize ; ++i)
    {
        printf("BS: ");
        printUint(i);
        arr[i] = readUint32_t(". element: ");
    }

    key = readUint32_t("BS: Enter the key: ");
    high = arraySize - 1;

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
    printf("Binary Search: Terminated...\n");

    exit(exit_success);
}

void linearSearch()
{
    printf("Linear Search: Started...\n");

    const uint32_t ARRSIZE = 16;
    uint32_t arr[ARRSIZE];
    uint32_t arraySize = 0;
    uint32_t key = 0, index = -1;
    
    arraySize = readUint32_t("LS: Enter size of array: ");

    for (uint32_t i = 0 ; i < arraySize ; ++i)
    {
        printf("LS: ");
        printUint(i);
        arr[i] = readUint32_t(". element: ");
    }

    key = readUint32_t("LS: Enter the key: ");

    for (uint32_t i = 0 ; i < arraySize ; ++i)
        if (arr[i] == key)
        {
            index = i;
            break;
        }
    
    int32_t printArr[] = {index};
    print("Linear search result: %d\n", 1, printArr);
    printf("Linear search: Terminated...\n");
    
    exit(exit_success);
}

void collatz()
{
    printf("Collatz: Started...\n");

    int32_t printArr[1];
    uint32_t lowerBound = 0, upperBound = 0;

    lowerBound = readUint32_t("Collatz: Enter the lower bound of collatz: ");
    upperBound = readUint32_t("Collatz: Enter the upper bound of collatz: ");

    for (uint32_t i = lowerBound ; i <= upperBound ; ++i)
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

    printf("Collatz: Terminated...\n");
    exit(exit_success);
}