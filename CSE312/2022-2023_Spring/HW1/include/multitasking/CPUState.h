#ifndef _CPU_STATE_H_
#define _CPU_STATE_H_

#include <common/types.h>

using namespace myos::common;

struct CPUState
{
    // what we push in the interrupt step
    uint32_t eax;
    uint32_t ebx;   // base register
    uint32_t ecx;   // counting register
    uint32_t edx;   // data register

    uint32_t esi;   // stack index
    uint32_t edi;   // data index
    uint32_t ebp;   // stack base pointer

    uint32_t error;

    // pushed by processor
    uint32_t eip;       // instruction pointer
    uint32_t cs;        // code segment
    uint32_t eflags;    // flags
    uint32_t esp;       // stack poiner
    uint32_t ss;        // stack segment - no need it beacuse esp is enough itself. ss is unnecessary
} __attribute__((packed));

#endif