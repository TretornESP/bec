int suma(int a, int b) {
    return a + b;
}
int resta(int a, int b) {
    return a - b;
}
int multiplicacion(int a, int b) {
    return a * b;
}

int division(int a, int b) {
    return a / b;
}

int main() {
    int i = 5; //0000 0101
    int j = 6; //0000 0110
    int x = 0xc2; //1100 0010
                  //1110 0000
                  //1100 0000
                  //0000 0110
    //j << 1   //0001 1000
    printf("i %x\n", i);
    printf("~i %x\n", ~i);
    printf("i&j %x\n", i&j);
    printf("i|j %x\n", i|j);
    printf("i^j %x\n", i^j);
    printf("j << 1 %d\n", j <<1);

    printf("3MSB de x: %x\n", (x&0xE0) >> 5);


}