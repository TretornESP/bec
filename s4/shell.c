#include <stdio.h>
#include <string.h>

unsigned char code[]= "\x6a\x01\x5f\xeb\x17\x5e\x6a\x09\x5a\x48\xff\xc2\x48\x31\xc0\x48\xff\xc0\x0f\x05\x6a\x3c\x58\x48\x31\xff\x0f\x05\xe8\xe4\xff\xff\xff\x48\x6f\x6c\x61";
int main(){
    printf("length of your shellcode is: %d\n", (int)strlen(code));
    int (*ret)() = (int(*)())code;
    ret();
}