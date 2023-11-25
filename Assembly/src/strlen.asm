global strlen
strlen:
    push rbp
    mov rbp, rsp
    xor rax, rax
.loop:
    cmp byte [rdi], 0
    je end
    inc rax
    inc rdi
    jmp .loop
end:
    pop rbp
    ret
