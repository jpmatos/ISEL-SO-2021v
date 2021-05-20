#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define DATA_SIZE 1*1024*1024

char data[DATA_SIZE * 2] = {1};
const char data_shared[DATA_SIZE * 2] = {1};
char bss[DATA_SIZE];


typedef struct __attribute__((packed)) tagChar {
    char  c;
} CHAR;

int main() {
    printf("PID: %u\n", getpid());

    ////////////////////////////////////////////////////
    ///a. Aumento do resident set (rss) na região que mapeia a secção de dados não iniciados (.bss)
    printf("#1-a (press ENTER to continue)"); getchar();

    ///Fill the array in .bss will increase RSS in this section
    for(int i = 0; i < sizeof(bss); i++)
        bss[i] = i;


    ////////////////////////////////////////////////////
    ///b. Aumento de páginas “private clean” na região que mapeia a secção de dados iniciados (.data)
    printf("#2-b (press ENTER to continue)"); getchar();

    ///Read from array in .data will increase private_clean in this section
    for(int i = 0; i < sizeof(data); i++){
        char b = data[i];
    }


    ////////////////////////////////////////////////////
    ///c. Criação de uma nova região de dados no espaço de endereçamento sem aumento do rss
    printf("#3-c (press ENTER to continue)"); getchar();

    ///Mapping a file from disk on memory will create a new region
    int fd = open("img.bmp", O_RDWR);
    struct stat buf;
    fstat(fd, &buf);
    off_t size = buf.st_size;
    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);


    ////////////////////////////////////////////////////
    ///d. Aumento do rss associado à nova região de dados
    printf("#4-d (press ENTER to continue)"); getchar();

    /// Reading from the mapped file will increase RSS in this region
    for (int i = 0; i < size; i++){
        CHAR *d_ptr = (CHAR *)(ptr + i);
        char d = d_ptr->c;
    }


    ////////////////////////////////////////////////////
    ///e. Criação de duas novas regiões, uma de código e outra de dados, no espaço de endereçamento
    printf("#5-e (press ENTER to continue)"); getchar();

    /// Mapping a file with PROT_READ | PROT_EXEC and MAP_PRIVATE will create a code region
    int fd_code = open("prog", O_RDWR);
    struct stat buf_code;
    fstat(fd_code, &buf_code);
    off_t size_code = buf_code.st_size;
    void *ptr_code = mmap(NULL, size_code, PROT_READ | PROT_EXEC, MAP_PRIVATE, fd_code, 0);

    /// Map another data region
    int fd_data = open("img2.bmp", O_RDWR);
    struct stat buf_data;
    fstat(fd_data, &buf_data);
    off_t size_data = buf_data.st_size;
    void *ptr_data = mmap(NULL, size_data, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd_data, 0);


    ////////////////////////////////////////////////////
    ///f. Aumento de páginas “private clean” na região que mapeia a secção de dados criada em e
    printf("#6-f (press ENTER to continue)"); getchar();

    for(int i = 0; i < size_data; i++){
        CHAR *f_ptr = (CHAR *)(ptr_data + i);
        char f = f_ptr->c;
    }


    ////////////////////////////////////////////////////
    ///g. Aumento do número de páginas “shared clean” na região que mapeia a secção de dados iniciados
    printf("#7-g (press ENTER to continue)"); getchar();

    pid_t pid = fork();
    if (pid == 0){
        for(int i = 0; i < sizeof(data_shared); i++){
            data_shared[i];
        }
    }

    printf("END (press ENTER to continue)"); getchar();
    return 0;
}

