			.data
str.size: 		.asciiz "Size: "
str.target_num:		.asciiz "Target number: "
str.element:		.asciiz ". element: "
str.error: 		.asciiz "Number should be non-negative! Please enter non-negative integer: "

str.possible:		.asciiz "Possible!"
str.not_possible:	.asciiz "Not Possible!"

arr.in:			.word 0 0 0 # address of array, size of array, capacity of array
arr.out:		.word 0 0 0 # address of array, size of array, capacity of array

			.text
			.globl main
main:
	la $a0, str.size
	la $a1, str.error
	jal getNonNegIntWithText
	addu $s0, $zero, $v0 # s0 = size
	
	la $a0, arr.in
	addu $a1, $zero, $s0
	jal initializeVector
	
	la $a0, arr.out
	and $a1, $a1, $zero
	jal initializeVector
	
	la $a0, str.target_num
	la $a1, str.error
	jal getNonNegIntWithText
	addu $s1, $zero, $v0 # s1 = target number
	
	la $a0, arr.in
	addu $a1, $zero, $s0
	jal fillVector

	addu $a0, $zero, $s1 # $a0 = target number
	la $t0, arr.in
	lw $a1, 0($t0) # $a1 = arr
	addu $a2, $zero, $s0 # $a2 = size
	jal checkSumPossibility
	addu $s3, $zero, $v0 # $s3 = returnVal
	
	addu $a0, $s3, $zero
	jal printResult
	
	la $t0, arr.out
	lw $a0, 0($t0)
	lw $a1, 4($t0)
	jal printArray
	
	la $t0, arr.in
	lw $a0, 0($t0)
	lw $a1, 4($t0)
	jal freeMemory
	
	la $t0, arr.out
	lw $a0, 0($t0)
	lw $a1, 4($t0)
	jal freeMemory
	
	addiu $v0, $zero, 10 # return main
	syscall

# Print message and gets non-negative integer. If user enters negative number, prints error message and again ask user a non-negative integer.
# $a0 = address of text, $a1 = address of error message text, $v0 = non-negative integer
getNonNegIntWithText:
	addiu $v0, $zero, 4 # print text
	syscall
	getNonNegIntWithTextLoop:
		addiu $v0, $zero, 5 # read integer
		syscall
		slt $t0, $v0, $zero
		beq $t0, $zero, getNonNegIntWithTextExit # if(integer > 0)
		addu $a0, $zero, $a1
		addiu $v0, $zero, 4 # print error text
		syscall
		j getNonNegIntWithTextLoop
	getNonNegIntWithTextExit:
	jr $ra

# Prints given array using given size on the screen.
# $a0 = address of array, $a1 = size of array
printArray:
	addu $t0, $zero, $a0 # $t0 = arr
	sll $t1, $a1, 2 # $t1 = size * 4
	add $t1, $t0, $t1 # $t1 = &arr[size]
	printArrayLoop:
		slt $t2, $t0, $t1
		beq $t2, $zero, printArrayExit
		addiu $a0, $zero, ' '
		addiu $v0, $zero, 11
		syscall # print space character
		lw $a0, 0($t0)
		addiu $v0, $zero, 1
		syscall # print array element
		addiu $t0, $t0, 4
		j printArrayLoop
	printArrayExit:
	jr $ra
	
# Checks whether if a subset of array elements can sum up to the target num.
# $a0 = target number, $a1 = adress of array, $a2 = size of array, $v0 = result of check sum possibility 0 or 1.
checkSumPossibility:
	bne $a0, $zero, checkSumPossibilityElse1
	addiu $v0, $zero, 1
	jr $ra
	checkSumPossibilityElse1:
	bne $a2, $zero, checkSumPossibilityElse2
	addiu $v0, $zero, 0
	jr $ra
	checkSumPossibilityElse2:
	addi $sp, $sp, -16
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	add $s0, $zero, $a0 # $s0 = target number
	add $s1, $zero, $a1 # $s1 = address of array
	add $s2, $zero, $a2 # $s2 = size of array
	lw $t0, 0($s1) # $t0 = *arr
	sub $t1, $s0, $t0 # $t1 = num - *arr
	slt $t2, $t1, $zero
	bne $t2, $zero, checkSumPossibilityElse3
		add $a0, $zero, $t1
		addi $a1, $s1, 4
		addi $t3, $zero, 1
		sub $a2, $s2, $t3
		jal checkSumPossibility
		beq $v0, $zero, checkSumPossibilityElse3
		la $a0, arr.out
		lw $t0, 0($s1) # $t0 = *arr
		addu $a1, $zero, $t0
		jal addItemToVector
		addiu $v0, $zero, 1
		j checkSumPossibilityReturn
	checkSumPossibilityElse3:	
	add $a0, $zero, $s0
	addi $a1, $s1, 4
	addi $t3, $zero, 1
	sub $a2, $s2, $t3
	jal checkSumPossibility
	checkSumPossibilityReturn:
	lw $s2, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 16
	jr $ra

# Print result of checkSumPossibility
# $a0 = state.
# Output = if state is 0, output is Not Possible. Otherwise, Possible.
printResult:
	bne $a0, $zero, printResultElse
		la $a0, str.not_possible
		addiu $v0, $zero, 4
		syscall
		j printResultReturn
	printResultElse:
	la $a0, str.possible
	addiu $v0, $zero, 4
	syscall
	printResultReturn:
	jr $ra

# Builds global output array. If capacity is less than or equal 0, capacity is 1 and size is 0.
# $a0 = address of struct head
# $a1 = capacity
initializeVector:
	addu $t0, $zero, $a0
	addu $t1, $zero, $a1
	slt $t2, $zero, $t1
	bne $t2, $zero, initializeVectorElse
	addiu $t1, $zero, 1
	initializeVectorElse:
	sll $t2, $t1, 2
	addu $a0, $zero, $t2
	addiu $v0, $zero, 9
	syscall # allocate memory
	sw $v0, 0($t0)
	sw $zero, 4($t0)
	sw $t1, 8($t0)
	jr $ra

# Adds item to vector. Performs reallocation if necessary.
# $a0 = address of struct head
# $a1 = item
addItemToVector:
	lw $t0, 0($a0)
	beq $t0, $zero, addItemToVectorExit
	addi $sp, $sp, -28
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)
	sw $s4, 20($sp)
	sw $s5, 24($sp)
	addu $s0, $zero, $a0	# $s0 = &struct
	lw $s1, 0($s0)		# $s1 = arr
	lw $s2, 4($s0)		# $s2 = size
	lw $s3, 8($s0)		# $s3 = capacity
	add $s4, $zero, $a1	# $s4 = item
	bne $s2, $s3, addItemToOutElse
		sll $s3, $s3, 1 # capacity *= 2
		sw $s3, 8($s0)
		sll $t0, $s3, 2 # $t0 = capacity * 4
		addu $a0, $zero, $t0
		addiu $v0, $zero, 9
		syscall
		addu $s5, $zero, $v0 # $s5 = newArr
		addu $t0, $zero, $s5 # $t0 = newArr
		addu $t1, $zero, $s1 # $t1 = arr
		and $t2, $t2, $zero # i = 0
		addItemToVectorLoop:
			slt $t3, $t2, $s2
			beq $t3, $zero, addItemToVectorLoopExit # if(i < size)
			sll $t4, $t2, 2
			addu $t0, $s5, $t4 # newArr = newArr + i
			addu $t1, $s1, $t4 # arr = arr + i
			lw $t5, 0($t1)
			sw $t5, 0($t0)
			addiu $t2, $t2, 1
			j addItemToVectorLoop
		addItemToVectorLoopExit:	
		addu $a0, $zero, $s1
		addu $a1, $zero, $s2
		jal freeMemory
		sw $s5, 0($s0)
		addu $s1, $zero, $s5 # arr = newArr
	addItemToOutElse:
	sll $t0, $s2, 2		# size *= 4
	addu $t0, $s1, $t0	# $t0 = arr + size
	sw $s4, 0($t0)		# arr[size] = item
	addiu $s2, $s2, 1	# used = used + 1
	sw $s2, 4($s0)
	lw $s5, 24($sp)
	lw $s4, 20($sp)
	lw $s3, 16($sp)
	lw $s2, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 28
	addItemToVectorExit:
	jr $ra

# Fills vector as much as given size
# $a0 = adress of struct, $a1 = size
fillVector:
	addi $sp, $sp, -16
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	addu $s0, $zero, $a0 # $s0 = adress of struct
	addu $s1, $zero, $a1 # $s1 = size
	and $s2, $s2, $zero # $s2 = 0
	fillVectorLoop:
	slt $t0, $s2, $s1
	beq $t0, $zero, fillVectorExit
		addu $a0, $zero, $s2
		addiu $a0, $a0, 1
		addiu $v0, $zero, 1
		syscall
		la $a0, str.element # i. positive element:
		la $a1, str.error
		jal getNonNegIntWithText
		addu $a0, $zero, $s0
		addu $a1, $zero, $v0
		jal addItemToVector
		addiu $s2, $s2, 1 # ++i
		j fillVectorLoop
	fillVectorExit:
	lw $s2, 12($sp)
	lw $s1, 8($sp)
	lw $s0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 16
	jr $ra

# Deallocates or sets zeros to memory
# $a0 = adress of block of memory
# $a1 = number of words to deallocate 
freeMemory:
	freeMemoryLoop:
		beq $a1, $zero, freeMemoryReturn
		sw $zero, 0($a0)
		addi $a0 , $a0, 4
		addi $a1, $a1, -1
		j freeMemoryLoop
	freeMemoryReturn:
	jr $ra
