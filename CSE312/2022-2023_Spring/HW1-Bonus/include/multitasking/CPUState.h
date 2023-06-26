#ifndef _CPU_STATE_H_
#define _CPU_STATE_H_

#include <common/types.h>

struct CPUState
{
    // what we push in the interrupt step
    myos::common::uint32_t eax;
    myos::common::uint32_t ebx;   // base register
    myos::common::uint32_t ecx;   // counting register
    myos::common::uint32_t edx;   // data register

    myos::common::uint32_t esi;   // stack index
    myos::common::uint32_t edi;   // data index
    myos::common::uint32_t ebp;   // stack base pointer

    myos::common::uint32_t error;

    // pushed by processor
    myos::common::uint32_t eip;       // instruction pointer
    myos::common::uint32_t cs;        // code segment
    myos::common::uint32_t eflags;    // flags
    myos::common::uint32_t esp;       // stack poiner
    myos::common::uint32_t ss;        // stack segment - no need it beacuse esp is enough itself. ss is unnecessary
} __attribute__((packed));

#endif