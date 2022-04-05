extern void main() {
    char * vga_ptr = (char*)0xb8000;
    *(vga_ptr) = 'C';
    *(vga_ptr+1) = (char)0x0f;

    while(1);
}