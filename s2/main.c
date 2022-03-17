#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

    int b = 5;
    int a[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    void * p = malloc(1);
    free(p);
    int fd = open("./boot.asm", O_RDWR);
    if (fd == -1) {
        printf("Error opening file\n");
        return 1;
    }
    void * q = mmap(0, 1, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS, 0, 0);
    char * r = (char*)mmap(0, 100, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE, fd, 0);
    if (r==MAP_FAILED) {
        printf("Error mmap\n");
    }
    for (int i = 0; i < 100; i++)
        printf("%c\n", r[i]);
    munmap(r, 1000);
    munmap(q, 1);
    close(fd);
}