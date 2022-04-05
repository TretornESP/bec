#include <unistd.h>
#include <stdio.h>
void p1();
void p2();

int a12, a13, a14;
int ready = 0;

int main(int argc, char *argv[]) {
	p1();
}

void kyield() {
	int a[10] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

	if (ready) {
		int tmp12 = a12;
		int tmp13 = a13;
		int tmp14 = a14;
		sleep(5000);
		a12 = a[12];
		a13 = a[13];
		a14 = a[14];
		a[12] = tmp12;
		a[13] = tmp13;
		a[14] = tmp14;
	} else {
		a12 = a[12];
		a13 = a[13];
		a14 = a[14];
		ready = 1;
		p2(); 
	}

	//Guarda ctx
	//Planificador
	//Restaura ctx
	return;
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
