global memset
memset:
    push rbx
    push rsi
    mov rbx, rdi
    mov rcx, rdx
.loop:
    cmp rcx, 0
    je .end
    mov BYTE [rdi], sil
    inc rdi
    dec rcx
    jmp .loop
.end:
    mov rax, rbx
    pop rsi
    pop rbx
    ret