section .data
	reqint db "Enter number: ", 0
	reqstring db "Enter string: ", 0
	fmt1in db "%d", 0
	fmt1out db "%d", 10, 0
	fmt2in: db "%s", 0
	fmt2out: db "%s", 10, 0

section .bss
	x: resd 1
	s: resb 100

global main
extern printf
extern scanf

section .text
main:
	push rbp
	lea rdi, [reqint]
	xor rax, rax
	call printf
	
	lea rdi, [fmt1in]
	lea rsi, [x]
	xor rax, rax
	call scanf

	lea rdi, [fmt1out]
	mov rsi, [x]
	xor rax, rax
	call printf

	lea rdi, [reqstring]
	xor rax, rax
	call printf

	lea rdi, [fmt2in]
	lea rsi, [s]
	xor rax, rax
	call scanf

	lea rdi, [fmt2out]
	lea rsi, [s]
	xor rax, rax
	call printf

	pop rbp
	mov rax, 0
	ret
