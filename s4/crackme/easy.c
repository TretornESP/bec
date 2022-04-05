#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int check(const char * str) {
    uint8_t* key = "BEC{s3cr3t_k3y}";
    return strcmp(key, str) == 0;
}

int main() {
    uint8_t str[40];
    scanf("%s", str);
    if (check(str)) {
        printf("Enhorabuena, pass correcta (:\n");
    } else {
        printf("Sigue intentándolo :(\n");
    }
}