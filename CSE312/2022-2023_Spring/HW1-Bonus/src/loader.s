.set MAGIC, 0x1badb002              # bootloader needs to see this magic number to accept it as a kernel
.set FLAGS, (1<<0 | 1<<1)           # bootloader's flags
.set CHECKSUM, -(MAGIC + FLAGS)     # for boot loader

.section .multiboot                 # put these fields to .o file
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernelMain                  # declaration of kernelMain in kernel.cpp
.extern callConstructors            # declaration of callConstructors in kernel.cpp
.global loader                      # entry point for loader.s

loader:
    mov $kernel_stack, %esp         # assign 2 MB field to stack pointer register
    pushl $(60413429)
    call callConstructors
    push %eax                       # multiboot structure for kernelMain
    push %ebx                       # magic number for kernelMain
    call kernelMain

_stop:                              # kernelMain will enter an infinite loop, it will never return here, but just in case, we made an infinite loop here too
    cli
    hlt
    jmp _stop

.section .bss
.space 2*1024*1024; # 2 MB
kernel_stack: