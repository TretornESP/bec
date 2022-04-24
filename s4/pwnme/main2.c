int main(int argc, char* argv[]) {
  char name[200];
  printf("%p\n", name);  // Print address of buffer.
  puts("What's your name?");
  strcpy(name, argv[1]);
  printf("Hello, %s!\n", name);
  return 0;
}