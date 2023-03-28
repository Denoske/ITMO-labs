%macro fill_registers_and_shuffle 1
    pxor xmm0, xmm0
    pxor xmm1, xmm1
    pxor xmm2, xmm2

    pinsrb xmm0, [rdi], 0
    pinsrb xmm1, [rdi+1], 0
    pinsrb xmm2, [rdi+2], 0

    pinsrb xmm0, [rdi+3], 12
    pinsrb xmm1, [rdi+4], 12
    pinsrb xmm2, [rdi+5], 12

    movdqa xmm3, [first_row]
    movdqa xmm4, [second_row]
    movdqa xmm5, [third_row]


    %if %1==1
        %define SHUFFLE_PATTERN 0b11000000
        %define MATRIX_SHUFFLE_PATTERN 0b11100100
    %elif %1==2
        %define SHUFFLE_PATTERN 0b11110000
        %define MATRIX_SHUFFLE_PATTERN 0b01001001
    %elif %1==3
        %define SHUFFLE_PATTERN 0b11111100
        %define MATRIX_SHUFFLE_PATTERN 0b10010010
    %endif

    shufps xmm0, xmm0, SHUFFLE_PATTERN
    shufps xmm1, xmm1, SHUFFLE_PATTERN
    shufps xmm2, xmm2, SHUFFLE_PATTERN

    shufps xmm3, xmm3, MATRIX_SHUFFLE_PATTERN
    shufps xmm4, xmm4, MATRIX_SHUFFLE_PATTERN
    shufps xmm5, xmm4, MATRIX_SHUFFLE_PATTERN
%endmacro

%macro calculate 0
    cvtdq2ps xmm0, xmm0
    cvtdq2ps xmm1, xmm1
    cvtdq2ps xmm2, xmm2

    mulps xmm0, xmm3
    mulps xmm1, xmm4
    mulps xmm2, xmm5

    addps xmm0, xmm1
    addps xmm0, xmm2

    cvtps2dq xmm0, xmm0
    mov r8, max_values
    pminsd xmm0, [r8]
%endmacro

%macro write_results 0
    pextrb [rsi],   xmm0,   0
    pextrb [rsi+1], xmm0,   4
    pextrb [rsi+2], xmm0,   8
    pextrb [rsi+3], xmm0,   12
%endmacro

%macro iterate 1
    fill_registers_and_shuffle %1
    calculate
    write_results
%endmacro

global sepia_asm

section .rodata
align 16
first_row: dd 0.131, 0.168, 0.189, 0.131
align 16
second_row: dd 0.534, 0.686, 0.769, 0.534
align 16
third_row: dd 0.272, 0.349, 0.393, 0.272
align 16
max_values: dd 255, 255, 255, 255



section .text
    sepia_asm:
        iterate 1
        add rdi, 3
        add rsi, 4

        iterate 2
        add rdi, 3
        add rsi, 4

        iterate 3
        add rdi, 3
        add rsi, 4
        ret
