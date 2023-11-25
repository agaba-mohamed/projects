global strchr
strchr:
    xor rax, rax
.loop:
    cmp BYTE [rdi + rax], sil
    je .gotit
    cmp BYTE [rdi + rax], 0
    je .end
    inc rax
    jmp .loop
.gotit:
    lea rax, [rdi + rax]  ;; lea = load effective address ; récup ladresse du rdi a partir de l'index rax
    ret
.end:
    xor rax, rax
    ret
