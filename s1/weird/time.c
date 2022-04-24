#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>

int fd;
#define SIZE   0x13d
#define OFFSET 0x1000
#define ROUNDS 100

static inline void func() {
    void * ptr = mmap(0, SIZE, PROT_READ|PROT_EXEC, MAP_PRIVATE, fd, OFFSET);
}
int main(int argc, char* argv[]) {
    uint64_t start[ROUNDS], end[ROUNDS];
    unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

    fd = open("./saluda.so", O_RDONLY);
    for (int i = 0; i < ROUNDS; i++) {

        asm volatile ("CPUID\n\t"
                    "RDTSC\n\t"
                    "mov %%edx, %0\n\t"
                    "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
                    "%rax", "%rbx", "%rcx", "%rdx");

        func();
        asm volatile("RDTSCP\n\t"
                    "mov %%edx, %0\n\t"
                    "mov %%eax, %1\n\t"
                    "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
                    "%rax", "%rbx", "%rcx", "%rdx");

        start[i] = ( ((uint64_t)cycles_high << 32) | cycles_low );
        end[i] = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 );
    }

    uint64_t starta = 0;
    uint64_t enda = 0;
    for (int i = 0; i < ROUNDS; i++) {
        //printf("S: %lu E:%lu\n", starta, enda);
        starta += start[i];
        enda += end[i];
    }
    starta = starta / ROUNDS;
    enda = enda / ROUNDS;

    printf("Average times: %lu\n", (enda-starta));
}