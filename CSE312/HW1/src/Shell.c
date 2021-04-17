char msg[] = "\n~ ";
char errmsg[] = "\nError! Wrong process.\n";

int main(void)
{
    char programName[30];
    int exit = 0;

    while(exit != 1)
    {
        asm("la $a0, msg\n\t"
            "addiu $v0, $zero, 4\n\t"
            "syscall");
        
        asm("add $t0, $zero, $fp\n\t"
            "addi $t0, $t0, 12\n\t"
            "move $a0, $t0\n\t"
            "addiu $a1, $zero, 30\n\t"
            "addiu $v0, $zero, 8\n\t"
            "syscall");

        asm("addiu $v0, $zero, 18\n\t"
            "syscall");

        asm("sw $v0, 8($fp)");

        if(exit == -1)
            asm("la $a0, errmsg\n\t"
                "addiu $v0, $zero, 4\n\t"
                "syscall");
    }

    return 0;
}