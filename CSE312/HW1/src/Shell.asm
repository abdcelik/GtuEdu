        .data
msg:
        .asciiz  "\012~ \000"
errmsg:
        .asciiz  "\012Error! Wrong process.\012\000"

        .text
        .globl main
main:
        addiu   $sp,$sp,-56
        sw      $fp,52($sp)
        move    $fp,$sp
        sw      $0,8($fp)
        b       $L2
$L3:
        la $a0, msg
        addiu $v0, $zero, 4
        syscall
        add $t0, $zero, $fp
        addi $t0, $t0, 12
        move $a0, $t0
        addiu $a1, $zero, 30
        addiu $v0, $zero, 8
        syscall
        addiu $v0, $zero, 18
        syscall
        sw $v0, 8($fp)
        lw      $3,8($fp)
        li      $2,-1                 # 0xffffffffffffffff
        bne     $3,$2,$L2
        la $a0, errmsg
        addiu $v0, $zero, 4
        syscall
$L2:
        lw      $3,8($fp)
        li      $2,1                        # 0x1
        bne     $3,$2,$L3
        move    $2,$0
        move    $sp,$fp
        lw      $fp,52($sp)
        addiu   $sp,$sp,56
        j       $31