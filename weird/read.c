#include <stdint.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

int main(int argc, char* argv[]) {
    signal(SIGINT, intHandler);
    int fd = open("/dev/shm/cuak", O_RDWR | O_CREAT, 00666);
    ftruncate(fd, 100);
    if (fd==-1) {
        perror("Error file!\n");
    }
    uint8_t *ptr = mmap(0, 100, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr != MAP_FAILED) {
        printf("Pointer at %p\n", ptr);
        while (keepRunning) {
            printf("%c\n", ptr[0]);
        }
    } else {
        perror("Mmap failed\n");
    }
    close(fd);
    remove("/dev/shm/cuak");
}