global strcmp
strcmp:
    xor rax, rax
.loop:
    mov dl, [rdi + rax]
    cmp dl, [rsi + rax]
    jne .inequal
    test dl, dl
    je .gotit
    inc rax
    jmp .loop
.inequal:
    sub dl, [rsi + rax]
    movsx rax, dl
    ret
.gotit:
    xor rax, rax
    ret
