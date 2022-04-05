#include <stdint.h>

struct status_register_bitfield {
    uint8_t h : 1;  //0
    uint8_t v : 1;  //0
    uint8_t c : 1;  //1
    uint8_t z : 1;  //0
    uint8_t i : 1;  //1
    uint8_t ie : 1; //0
    uint8_t n : 1;  //0
    uint8_t u : 5;  //0
} __attribute__((packed));

union status_register {
    struct status_register_bitfield bitfield;
    uint16_t value;
};

int main() {
    union status_register sr;
    sr.bitfield.h = 0;
    sr.bitfield.c = 1;
    sr.bitfield.i = 1;
    //0001 0100

    printf("%x\n", sr.value);
    sr.value = 0xFF;
    printf("%x\n", sr.bitfield.h);
}