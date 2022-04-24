#include <stdint.h>
#include <stdio.h>
#include <string.h>

void tiroenelpie() {
    system("/bin/sh");
}

int main(int argc, char* argv[]) {
    char buffer[128];
    printf("%p\n", buffer);
    printf("Como te llamas?\n");
    tiroenelpie();
    //gets(buffer);
    printf("Hola %s\n", buffer);
    return 0;
}

//gcc -fno-stack-protector main.c
