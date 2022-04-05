void error(void) {
    printf("Error\n");
}

void correcto(void) {
    printf("Correcto\n");
}

struct wtf {
    void (*func)(void);
    char password[32];
};

int main() {
    struct wtf cuak;
    printf("Enter password: ");
    cuak.func = error;
    gets(cuak.password);

    if (!strcmp(cuak.password, "secret")) {
        cuak.func = correcto;
    }
    cuak.func();
}