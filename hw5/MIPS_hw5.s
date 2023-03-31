# MIPS Assembly Basics: MIPS code that computes the
# nth power of 2. Assumes n is stored in $a0. Stores 
# the result of the computation in $v0. 

# ----------------------------------------
# Data declarations go in this section.
.data
        n: .asciiz "Enter a integer from 1 to 30: "
        result1: .asciiz " raised to "
        result2: .asciiz " gives: "
        nline: .asciiz "\n"
        
# ----------------------------------------
# Program code goes in this section.
.text
.globl  main
main:

# Prompt user for n that will be stored in $a0
        li $v0, 4
        la $a0, n 
        syscall #print prompt for a number

        li $v0, 5 # Get the users n
        syscall
        move $t1, $v0 # store result in $t0 

        addi $t0, $zero, 2 # store 2 in t0

        beq $t1,$zero,else #if (t1=0) go to else
        addi $t2,$zero,1 #otherwise t2=1, t1=n, t2=result
        addi $s4,$zero,0

loop:  #if s4<t1
        slt $s5,$s4,$t1 #$s5=($s4<$t1) if(n<21) $s5=1
        beq $s5,$zero,done #if $s5=0 then done
        mul $t2,$t2,$t0 #t2=t2*t0
        addi $s4,$s4,1 #s4=s4+1
        j loop

else:
        addi $t2,$zero,1
        j done

done: #The print statements
        li $v0,1
        move $a0,$t0
        syscall  #print 2
        li $v0,4
        la $a0,result1
        syscall  #print " raised to "
        li $v0,1
        move $a0,$t1
        syscall  #print n
        li $v0,4
        la $a0,result2
        syscall  #print " gives "
        li $v0,1
        move $a0,$t2
        syscall  #print result(t2)
        li $v0,4
        la $a0,nline
        syscall           #print nline

# -----
# Done, terminate program.
        li $v0, 10 # call code for terminate
        syscall # system call (all done!)
        
.end main

