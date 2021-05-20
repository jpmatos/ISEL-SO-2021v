	.file	"xopen.c"
	.text
	.globl	xopen
	.type	xopen, @function
xopen:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, %rsi      #copy str to first parameter
	movl	$511, %ecx      #copy access to second parameter
	movl	$1090, %edx     #copy permissions to third parameter
	movl	$2, %edi        #open() is no2
	call	syscall
	leave
	ret
