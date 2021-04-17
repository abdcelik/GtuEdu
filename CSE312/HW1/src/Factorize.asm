		.data 
msg.comma:	.asciiz ","
msg.newline:	.asciiz "\n"
msg.get:	.asciiz "Please enter a positive integer: "
msg.error:	.asciiz "Error! Given integer must be positive!\n"
		.text
		.globl main

main:
	getPosInt:
	
	la $a0, msg.get
	addiu $v0, $zero, 4
	syscall			# print message

	addiu $v0, $zero, 5
	syscall			# get integer from user
	
	slt $t0, $zero, $v0
	bne $t0, $zero, Exit
		la $a0, msg.error
		addiu $v0, $zero, 4
		syscall			# print error message
		j getPosInt
	Exit:
	
	addu $a0, $zero, $v0
	jal factorize
	
	addiu $v0, $zero, 10
	syscall			# terminate execution

# $a0 -> given number
factorize:
	addiu $t0, $zero, 1	# $t0 = 0
	addu $t1, $zero, $a0	# $t1 = num
	
	factorizeLoop:
		slt $t2, $t1, $t0
		bne $t2, $zero, factorizeReturn
	
		div $t1, $t0
		mfhi $t2
		
		bne $t2, $zero, factorizeExit
		
		addu $a0, $zero, $t0
		addiu $v0, $zero, 1
		syscall			# print factor
		
		beq $t1, $t0, factorizeLast
		
		la $a0, msg.comma
		addiu $v0, $zero, 4
		syscall			# print comma character
		
		j factorizeExit
		
		factorizeLast:
		la $a0, msg.newline
		addiu $v0, $zero, 4
		syscall			#print newline character
		
		
		factorizeExit:
		addiu $t0, $t0, 1
		j factorizeLoop
		
	factorizeReturn:
	jr $ra