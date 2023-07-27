Homework Grade: 75

In the folder where the makefile is located, open terminal.
    Command is 'make run microkernel=obj/KERNEL.o'

You must change the KERNEL for desired microkernel.
List of micro kernels you can use:
    - make run microkernel=obj/kernel1.o
    - make run microkernel=obj/kernel2.o
    - make run microkernel=obj/kernel3.o

If you are going to run different kernels,
    you should type 'make clean' after each use of make run.

IMPORTANT NOTE:
    - Given input array for binary search in the assignment pdf is not sorted.
        Therefore, given output is not correct. The correct output is -1. Means that result could not be found.

    - Processes running collatz in microkernels produce a lot of output.
        This makes it very difficult to follow the screen.
        For this reason, collatz operates the [20, 25) interval, not the [1,25) interval. (Just to be able to follow the screen)
