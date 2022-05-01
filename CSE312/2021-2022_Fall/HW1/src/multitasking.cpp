
#include <multitasking.h>

using namespace myos;
using namespace myos::common;


Task::Task(GlobalDescriptorTable *gdt, void entrypoint())
{
    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));
    
    cpustate -> eax = 0;
    cpustate -> ebx = 0;
    cpustate -> ecx = 0;
    cpustate -> edx = 0;

    cpustate -> esi = 0;
    cpustate -> edi = 0;
    cpustate -> ebp = 0;
    
    /*
    cpustate -> gs = 0;
    cpustate -> fs = 0;
    cpustate -> es = 0;
    cpustate -> ds = 0;
    */
    
    // cpustate -> error = 0;    
   
    // cpustate -> esp = ;
    cpustate -> eip = (uint32_t)entrypoint;
    cpustate -> cs = gdt->CodeSegmentSelector();
    // cpustate -> ss = ;
    cpustate -> eflags = 0x202;
    
}

Task::~Task()
{
}

        
TaskManager::TaskManager()
{
    numTasks = 0;
    currentTask = -1;
}

TaskManager::~TaskManager()
{
}

bool TaskManager::AddTask(Task* task)
{
    if(numTasks >= 256)
        return false;
    tasks[numTasks++] = task;
    return true;
}

CPUState* TaskManager::Schedule(CPUState* cpustate)
{
    bool exitflag = false;

    while(!exitflag)
    {
        if(numTasks <= 0)
            return cpustate;
        
        if(currentTask >= 0)
            tasks[currentTask]->cpustate = cpustate;
        
        if(++currentTask >= numTasks)
            currentTask %= numTasks;

        if(!tasks[currentTask]->terminated)
            exitflag = true;
    }

    return tasks[currentTask]->cpustate;
}

MyThread::MyThread(TaskManager* threMan): threadManager(threMan)
{
    
}

void MyThread::create_thread(Task* thread)
{
    threadManager->AddTask(thread);
}

void MyThread::terminate_thread(int threadId)
{
    threadManager->tasks[threadId]->terminated = true;
    while(true);
}