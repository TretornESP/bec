#include <stdio.h>
int main() {
  char name[128];
  printf("%p\n", name);  // Print address of buffer.
  puts("What's your name?");
  gets(name);
  printf("Hello, %s!\n", name);
  return 0;
}


//libc: 7ffff7dcd000
//system: 522c0
//first gadget: 23b72


//0x7ffff7dcd000+0x00000000000522c0
//??
//0x7ffff7dcd000+0x23b72
