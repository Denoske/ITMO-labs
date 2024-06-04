.macro push %s
    sw zero, 0(%s)
.end_macro

.macro pop %d, %s
    lw %d, 1(%s)
.end_macro
            .text
start:      mv    a0, zero
fifo:       addi  a0, a0, 1
            push  a0
            addi  a0, a0, 1
            push  a0
            addi  a0, a0, 1
            push  a0
            addi  a0, a0, 1
            push  a0
            addi  a0, a0, 1
            push  a0
            addi  a0, a0, 1
            push  a0
            addi  a0, a0, 1
            push  a0
            addi  a0, a0, 1
            push  a0
            addi  a0, a0, 1
            push  a0
            addi  a0, a0, 1
            push  a0
	    mv    a1, zero
            pop   a0, a1    #0 
            addi  a1, a1, 1
            pop   a0, a1    #1
            addi  a1, a1, 1
            pop   a0, a1    #2
            addi  a1, a1, 1
            pop   a0, a1    #3
            addi  a1, a1, 1
            pop   a0, a1    #4
            addi  a1, a1, 1
            pop   a0, a1    #5
            addi  a1, a1, 1
            pop   a0, a1    #6
            addi  a1, a1, 1
            pop   a0, a1    #7
            addi  a1, a1, 1
            pop   a0, a1    #8
