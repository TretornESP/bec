#include <string.h>
#include <dlfcn.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
int fd;
#define SIZE   0x13d
#define OFFSET 0x1000

int main(int argc, char *argv[]) {
    fd = open("./saluda.so", O_RDONLY);
    void * ptr = mmap(0, SIZE, PROT_READ|PROT_EXEC, MAP_PRIVATE, fd, OFFSET);

    while(1);
}