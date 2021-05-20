CC=gcc
CFLAGS=-I.

main: main.c syscalls.o
	gcc main.c syscalls.o -o main

syscalls.o: syscalls.s
	gcc -c syscalls.s -o syscalls.o

# xgetpid.s: xgetpid.c
# 	gcc -S -O0 xgetpid.c

# xopen.o: xopen.s
# 	gcc -c xopen.s -o xopen.o

# xopen.s: xopen.c
# 	gcc -S -O0 xopen.c

# xwrite.o: xwrite.s
# 	gcc -c xwrite.s -o xwrite.o

# xwrite.s: xwrite.c
# 	gcc -S -O0 xwrite.c

# xclose.o: xclose.s
# 	gcc -c xclose.s -o xclose.o

# xclose.s: xclose.c
# 	gcc -S -O0 xclose.c
