int main() {
    char buffer[30];
    gets(buffer);
    printf("main at %p, buffer at %p\n", main, buffer);
    printf(buffer);
}