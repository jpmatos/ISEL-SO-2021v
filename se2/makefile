prog: prog.c syscalls.o syscalls.h
	gcc prog.c syscalls.o -o prog

syscalls.o: syscalls.s
	gcc -c syscalls.s -o syscalls.o
