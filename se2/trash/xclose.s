	.file	"xclose.c"
	.text
	.globl	xclose
	.type	xclose, @function
xclose:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, %esi
	movl	$3, %edi
	call	syscall
	leave
	ret
