		.data
msg.prime:	.asciiz " prime\n"
msg.notprime:	.asciiz "\n"

		.text
		.globl main

main:
	jal showPrimes
			
	addiu $v0, $zero, 10
	syscall

showPrimes:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	addiu $s0, $zero, 0
	addiu $s1, $zero, 1000
	
	showPrimesLoop:
		slt $t0, $s1, $s0
		bne $t0, $zero, showPrimesReturn
		
		addu $a0, $zero, $s0
		addiu $v0, $zero, 1
		syscall
		
		addu $a0, $zero, $s0
		jal isPrime
		
		beq $v0, $zero, showPrimesElse
		
		la $a0, msg.prime
		addiu $v0, $zero, 4
		syscall
		j showPrimesExit
		
		showPrimesElse:
		
		la $a0, msg.notprime
		addiu $v0, $zero, 4
		syscall
		
		showPrimesExit:
		
		addi $s0, $s0, 1
		j showPrimesLoop
		
	showPrimesReturn:
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra

# Returns 1 if given number is prime. Otherwise returns 0.
# $a0 = number, $v0 = result
isPrime:
	addiu $t0, $zero, 2
	slt $t1, $a0, $t0
	beq $t1, $zero, isPrimeElse # if (num < 2)
	addiu $v0, $zero, 0
	jr $ra
	isPrimeElse:
	
	srl $t1, $a0, 1		# $t1 -> num / 2
	addu $t2, $zero, $a0	# t2 -> num
	
	isPrimeLoop:
		slt $t3, $t1, $t0
		bne $t3, $zero, isPrimeReturn1
		div $t2, $t0
		mfhi $t4
		beq $t4, $zero, isPrimeReturn0
		addiu $t0, $t0, 1
		j isPrimeLoop

	isPrimeReturn0:
	addiu $v0, $zero, 0
	j isPrimeReturn
	
	isPrimeReturn1:
	addiu $v0, $zero, 1

	isPrimeReturn:
	jr $ra
