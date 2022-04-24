int main() {
    char val = 'a';
    char addr;
    __asm__ ("movb %0,%1"::"r" (val), "m" (addr));
}