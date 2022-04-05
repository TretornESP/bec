#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <elf.h>

int main() {
    
    int fd = open("./lib.so", S_IRWXG);
    if (fd == -1) {
        printf("Error en open\n");
        return 1;
    }

    struct stat st;
    fstat(fd, &st);

    printf("Size of file: %d\n", st.st_size);
    uint8_t * lib_buffer = mmap(0, st.st_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if (lib_buffer == 0) {
        printf("malloc error\n");
        return 1;
    }

    printf("File descriptor: %d\n", fd);
    printf("Buffer at: %p\n", lib_buffer);

    int result = read(fd, lib_buffer, st.st_size);
    if (result == -1) {
        printf("Read error\n");
        return 1;
    }

    for (int i = 0; i < 10; i++)
        printf("b[%d] %c ",i, lib_buffer[i]);

    Elf64_Ehdr *header = (Elf64_Ehdr *)lib_buffer;
    Elf64_Off segment_table = header->e_phoff;
    uint16_t segment_entry_size = header->e_phentsize;
    uint16_t segment_number = header->e_phnum;

    Elf64_Off section_table = header->e_shoff;
    uint16_t section_entry_size = header->e_shentsize;
    uint16_t section_number = header->e_shnum;

    uint16_t string_tab = header->e_shstrndx;

    Elf64_Shdr *string_section = (Elf64_Shdr*)&lib_buffer[(section_table+(string_tab*section_entry_size))];

    for (int i = 0; i < string_section->sh_size; i++) {
        printf("%c", lib_buffer[string_section->sh_offset+i]);
    }

    printf("\nstrtab at %d\n", string_tab);

    for (int i = 0; i < section_number; i++) {
        printf("Section %i at %x named:\n", i, section_table+(i*section_entry_size));
    }

    for (int i = 0; i < header->e_phnum; i++) {
        printf("Segment %i at %x\n", i, segment_table+(i*segment_entry_size));
    }
}