.macro push %s
    sw zero, 0(%s)
.end_macro

.macro pop %d
    lw %d, 0(zero)
.end_macro
            .text
start:      mv    a0, zero
fifo:       addi  a0, a0, 8
            push  a0
            addi  a0, a0, 7
            push  a0
            addi  a0, a0, 6
            push  a0
            addi  a0, a0, 5
            push  a0
            addi  a0, a0, 4
            push  a0
            addi  a0, a0, 3
            push  a0
            addi  a0, a0, 2
            push  a0
            addi  a0, a0, 1
            push  a0
            pop   a1
            pop   a1
            pop   a1
            pop   a1
            pop   a1
            pop   a1
            pop   a1
            pop   a1


