#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t* XORCipher(uint8_t* data, uint8_t* key, int dataLen, int keyLen) {
	uint8_t* output = (uint8_t*)malloc(sizeof(uint8_t) * dataLen);

	for (int i = 0; i < dataLen; ++i) {
		output[i] = data[i] ^ key[i % keyLen];
	}

	return output;
}



void winner() {
    printf("Enhorabuena, pass correcta (:\n");
}

int check(char * str) {
    uint8_t* password = "\x31\x20\x20\x9\x35\x40\x0\x16\x14\x42\x17\x10\x2c\x54\x10\x2d\xd\x40\x1\x1\x1e";
    uint8_t* key = "secret";
    uint8_t* plainText = XORCipher(str, key, strlen(str), strlen(key));

    for (int i = 0; i < 22; i++) {
        if (plainText[i] != password[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    uint8_t str[40];
    scanf("%s", str);
    if (check(str)) {
        winner();
    } else {
        printf("Sigue intentándolo :(\n");
    }
}