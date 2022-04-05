#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char buffer[64];
    gets(buffer);

    if (strcmp(buffer, "password") == 0) {
        printf("okay\n");
        exit(0);
    }
    printf("mal\n");
    return 0;
}

//gcc -fno-stack-protector main.c
