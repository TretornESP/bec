#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    char buffer[16];
    printf("Enter your name: ");
    fgets(buffer, 32, stdin);
    puts("Hello");
    printf(buffer, 32);
    printf("This is the totally secure service, enter a query: ");
    fgets(buffer, 256, stdin);
    puts("CUak");
    return 0;
}