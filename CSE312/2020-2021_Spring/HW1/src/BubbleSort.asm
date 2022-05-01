		.data
msg.size:	.asciiz "Enter the size: "
msg.size_err:	.asciiz "Error! Size must be positive integer.\n"
msg.item:	.asciiz ". item: "
msg.comma:	.asciiz ", "
msg.newline:	.asciiz "\n"
		.text
		.globl main

main:
	getPosInt:
	la $a0, msg.size
	addiu $v0, $zero, 4
	syscall			# print size message
	
	addiu $v0, $zero, 5
	syscall			# read integer
	
	slt $t0, $zero, $v0
	bne $t0, $zero, getPostIntExit

	la $a0, msg.size_err
	addiu $v0, $zero, 4
	syscall
	j getPosInt

	getPostIntExit:
	
	addu $s0, $zero, $v0	# $s0 -> size
	
	addu $a0, $zero, $s0
	sll $a0, $a0, 2
	addiu $v0, $zero, 9
	syscall			# allocate memory
	
	addu $s1, $zero, $v0	# $s1 -> arr
	
	addu $a0, $zero, $s1
	addu $a1, $zero, $s0
	jal getInt
	
	addu $a0, $zero, $s1
	addu $a1, $zero, $s0
	jal BubbleSort
	
	addu $a0, $zero, $s1
	addu $a1, $zero, $s0
	jal printArr
	
	addiu $v0, $zero, 10
	syscall			# terminate execution
	
# $a0 -> address of dynamic array
# $a1 -> size of array
BubbleSort:
	addi $sp, $sp, -28
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)
	sw $s4, 20($sp)
	sw $s5, 24($sp)

	addu $s0, $zero, $a0	# $t0 = address of dynamic array
	addu $s1, $zero, $a1	# $t1 = size of array

	and $s2, $s2, $zero	# i = 0
	addiu $s3, $s1, -1	# size - 1
	
	loop_i:
		slt $t9, $s2, $s3
		beq $t9, $zero, loop_i_exit
		and $s4, $s4, $zero	# j = 0
		sub $s5, $s3, $s2	# size - 1 - i
		loop_j:
			slt $t9, $s4, $s5
			beq $t9, $zero, loop_j_exit
			
			sll $t0, $s4, 2
			addu $t1, $t0, $s0
			lw $t2, 0($t1)		# arr[j]
			lw $t3, 4($t1)		# arr[j+1]
			
			slt $t9, $t2, $t3
			bne $t9, $zero, ifExit
			
			addu $a0, $zero, $t1
			jal swap
			
			ifExit:
			addiu $s4, $s4, 1
			j loop_j
			
		loop_j_exit:
		addiu $s2, $s2, 1
		j loop_i
		
	loop_i_exit:
	
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	lw $s4, 20($sp)
	lw $s5, 24($sp)
	addi $sp, $sp, 28
	jr $ra

# $a0 -> address of sequence item
swap:
	lw $t0, 0($a0)
	lw $t1, 4($a0)
	addu $t2, $zero, $t0
	addu $t0 $zero, $t1
	addu $t1, $zero, $t2
	sw $t0, 0($a0)
	sw $t1, 4($a0)
	jr $ra

# $a0 -> address of dynamic array
# $a1 -> size of array
getInt:
	addu $t0, $zero, $a0	# arr
	addu $t1, $zero, $a1	# size
	addiu $t2, $zero, 0	# i = 0
	
	getIntLoop:
		slt $t3, $t2, $t1
		beq $t3, $zero, getIntReturn
		
		addu $a0, $zero, $t2
		addiu $a0, $a0, 1
		addiu $v0, $zero, 1
		syscall			# print i+1
		
		la $a0, msg.item
		addiu $v0, $zero, 4
		syscall			# print ".item" message
		
		addiu $v0, $zero, 5
		syscall			# get integet
		
		sll $t3, $t2, 2
		addu $t4, $t0, $t3
		sw $v0, 0($t4)		# place integer to postion
		
		addiu $t2, $t2, 1 
	j getIntLoop
	
	getIntReturn:
	jr $ra

# $a0 -> address of dynamic array
# $a1 -> size of array
printArr:
	addu $t0, $zero, $a0	# arr
	addi $a1, $a1, -1
	sll $t1, $a1, 2		# size * 4
	addu $t1, $t1, $a0	# arr + size
	
	printArrLoop:
		slt $t2, $t1, $t0
		bne $t2, $zero, printArrReturn
		
		lw $a0, 0($t0)
		addiu $v0, $zero, 1
		syscall
		
		beq $t0, $t1, printArrElse
			la $a0, msg.comma
			addiu $v0, $zero, 4
			syscall
			j printArrExit
			
		printArrElse:
			la $a0, msg.newline
			addiu $v0, $zero, 4
			syscall
			j printArrExit
		
		printArrExit:
		addiu $t0, $t0, 4
		j printArrLoop
		
	printArrReturn:
	jr $ra
