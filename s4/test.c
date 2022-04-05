unsigned char * XORCipher(char * input_user,char* clave,int longitud_input,int longitud_clave)

{
  unsigned char *buffer_xored;
  int i;
  
  buffer_xored = malloc((long)longitud_input);

  for (i = 0; i < longitud_input; i = i + 1) {
    buffer_xored[i] = input_user[i] ^ clave[i % longitud_clave];
  }
  return buffer_xored;
}

int main() {
    unsigned char * input = "\x31\x20\x20\x09\x35\x40\x00\x16\x14\x42\x17\x10\x2C\x54\x10\x2D\x0D\x40\x01\x01\x1E";
    unsigned char * secret = "secret";
    char * decoded = XORCipher(input, secret, 22, 6);
    printf("%s\n", decoded);
}