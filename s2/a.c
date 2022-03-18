#include <unistd.h>
#include <stdio.h>
void p1();
void p2();

int main(int argc, char *argv[]) {
	p1();
	p2();
}

void kyield() {
	//Guarda ctx
	//Kernel hace cosas
	//Planificador
	//Restaura ctx
}

void kwrite(const char * str) {
	kyield();
	write(1, str, 1);
}

void p1() {
	int i = 10;
	while (i--) {
		kwrite("a");
	}
}

void p2() {
	int i = 10;
	while (i--) {
		kwrite("b");
	}
}
