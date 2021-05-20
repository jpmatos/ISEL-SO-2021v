	.text
	.globl	xgetpid
	.type	xgetpid, @function
xgetpid:
	movl	$39, %edi       #getpid() is no39
	call	syscall
	ret

	.globl	xopen
	.type	xopen, @function
xopen:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, %rsi
	movl	$511, %ecx
	movl	$1090, %edx
	movl	$2, %edi        #open() is no2
	call	syscall
	leave
	ret

	.globl	xwrite
	.type	xwrite, @function
xwrite:
	movq	%rdx, %rcx
	movq	%rsi, %rdx
	movl	%edi, %esi
	movl	$1, %edi        #write() is no1
	call	syscall
	ret

	.globl	xclose
	.type	xclose, @function
xclose:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, %esi
	movl	$3, %edi        #close() is no3
	call	syscall
	leave
	ret
