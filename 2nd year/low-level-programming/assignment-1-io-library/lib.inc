section .text
 
 
; Принимает код возврата и завершает текущий процесс
exit: ; di - excode
    mov rax, 60
    syscall
ret 

; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length: ; di - str ptr
    cld
    xor al, al
    mov rcx, 0xffffffff
    repne scasb
    mov rax, 0xfffffffe
    sub rax, rcx
ret

; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string: ; di = str ptr
    mov rsi, rdi
    call string_length
    mov rdi, rsi
    mov rdx, rax

    mov rax, 1
    mov rsi, rdi
    mov rdi, 1

    syscall

ret

; Принимает код символа и выводит его в stdout
print_char: ; di = char
    dec rsp
    mov byte [rsp], dil

    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1
    syscall

    inc rsp

ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
   mov rdi, `\n`
   jmp print_char

ret

; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint: ; di - uint
    mov rax, rdi
    mov rsi, 10
    mov r10, rsp
    dec rsp
    mov byte [rsp], 0
    .divide:
        xor rdx, rdx
        div rsi
        add dl, '0'
        dec rsp
        mov [rsp], dl
        test rax, rax
        jnz .divide
    mov rdi, rsp
    call print_string
    mov rsp, r10
    ret



; Выводит знаковое 8-байтовое число в десятичном формате 
print_int: ; di - number
    test rdi, rdi
    jns .sign
    push rdi
    mov rdi, '-'
    call print_char
    pop rdi
    neg rdi
    .sign:
       jmp print_uint


; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
    push rdi
    call string_length
    push rax
    mov rdi, rsi
    call string_length
    pop rcx
    pop rdi
    cmp rcx, rax
    mov rcx, 0
    cmovne rax, rcx
    jne ._end

    mov rcx, rax
    repe cmpsb
    mov rdx, 1
    xor rax, rax
    or rcx, rcx
    cmovz rax, rdx

._end:

ret

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    dec rsp
    xor rax, rax
    xor rdi, rdi
    mov rsi, rsp
    mov rdx, 1
    syscall
    test rax, rax
    jz ._eof
    mov al, byte [rsp]
    inc rsp
ret 
    ._eof:
        inc rsp
ret

; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор
read_word: ; di - buf, si - bufsize
    dec rsi
    push rsi
    push rdi

    xor r8, r8
    xor r9, r9
    ._loop: 
        call read_char
        test r8, r8
        jnz .ncheck

        cmp al, ` `
        je ._loop
        cmp al, `	`
        je ._loop
        cmp al, `\n`
        je ._loop
        cmp al, 4
        je ._e_loop_1
        test al, al
        je ._e_loop_1
        inc r8
        .ncheck:
        cmp al, ` `
        je ._e_loop_1
        cmp al, `	`
        je ._e_loop_1
        cmp al, `\n`
        je ._e_loop_1
        test al, al
        je ._e_loop_1
        cmp al, 4
        je ._e_loop_1
        cmp al, 10
        je ._e_loop_1
        inc r9
        mov rdi, qword [rsp+8]
        cmp r9, rdi
        ja ._e_loop_2

        mov rdi, qword [rsp]
        mov byte [rdi+r9-1], al
        xor al, al
        jmp ._loop

        ._e_loop_1:
            pop rax
            add rsp, 8
            mov byte [rax+r9], 0
            mov rdx, r9
ret
        ._e_loop_2:
            add rsp, 16
            xor rax, rax
ret  



; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint: ; di - str
    xor rax, rax
    xor rcx, rcx
    mov rsi, 10
    .compare:
        mov r10, 0
        mov r10b, byte [rdi+rcx]
        cmp r10b, '9'
        ja .end
        cmp r10b, '0'
        jb .end
        inc rcx
        mul rsi
        sub r10, `0`
        add rax, r10
        jmp .compare
    .end:
        mov rdx, rcx
        ret



; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int: ; di - str
    mov al, byte [rdi]
    cmp al, '-'
    je .negative
    jmp parse_uint
    .negative:
        inc rdi
        call parse_uint
        neg rax
        test rdx, rdx
        jz .skip
        inc rdx
    .skip:
        ret


; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy: ; di - str ptr, si - buf ptr, dx - buf len
    push rdi
    call string_length
    pop rdi
    inc rax

    mov rcx, rsi
    mov rsi, rdi ;xchg rdi, rsi
    mov rdi, rcx

    cmp rdx, rax
    jae ._buf_bigger

    xor rax, rax
ret

    jmp ._end

    ._buf_bigger:
        mov rcx, rax
        rep movsb
._end:

ret
