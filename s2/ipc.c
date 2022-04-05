#include<sys/ipc.h>
#include<sys/shm.h>
#include <sys/mman.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int shmkey = 69420;//u can choose it as your choice

int main() {
    int shmem = shmget(shmkey, 1024, IPC_CREAT | 0666);
    if (shmem == -1) {
        perror("shmget");
        exit(1);
    }

    char *shm = shmat(shmem, 0, 0);
    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    shm[0] = 'a';

    while (1) {
        *status_pointer = 0;
        printf("%c\n", *shm);
        sleep(3);
        *status_pointer = 1;
    }
}