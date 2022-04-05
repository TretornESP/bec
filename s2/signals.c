#include <signal.h> /* signal() */

void handler(int sig)
{
    /* undefined behavior, maybe fine on specific platform */
    printf("Catched: %d\n", sig);
}

int main() {
    signal(9, &handler);
    void *p = 0x0000;
    //*(int*)p = 0;
    while (1);
}