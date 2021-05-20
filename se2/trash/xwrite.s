	.file	"xwrite.c"
	.text
	.globl	xwrite
	.type	xwrite, @function
xwrite:
	movq	%rdx, %rcx      #3rd arg
	movq	%rsi, %rdx      #2nd arg
	movl	%edi, %esi      #1st arg
	movl	$1, %edi        #write is no1
	call	syscall
	ret
