#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char buffer[16];

    printf("Enter your name: ");
    fgets(buffer, 32, stdin);
    puts("Hola");
    printf(buffer, 32);
    printf("This is the totally secure server, enter your query: ");
    fgets(buffer, 256, stdin);
    puts("Llega");
}