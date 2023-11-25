global strncmp
strncmp:
    xor rcx, rcx
.loop:
    cmp rcx, rdx
    je .gotit
    mov al, [rdi + rcx]
    cmp al, [rsi + rcx]
    jne .infound
    cmp al, 0
    je .gotit
    inc rcx
    jmp .loop
.infound:
    sub al, [rsi+rcx]
    movsx eax, al
    ret
.gotit:
    xor eax, eax
    ret
    