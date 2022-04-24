#include <stdint.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
    int fd = open("/dev/shm/cuak", O_RDWR);
    if (fd == -1) {
        printf("FD Error\n");
    }
    uint8_t *ptr = mmap(0, 100, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr != MAP_FAILED) {
        ptr[0] = 'c';
    } else {
        printf("Mmap error\n");
    }
    munmap(ptr, 100);
    close(fd);
}