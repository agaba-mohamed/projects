global memcpy
memcpy:
    mov rcx, rdx
    mov rax, rdi
.loop:
    dec rcx
    js .end
    mov al, [rsi]
    mov [rdi], al
    inc rsi
    inc rdi
    jmp .loop
.end:
    ret
