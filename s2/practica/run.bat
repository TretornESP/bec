wsl rm -r obj/*
wsl rm -r bin/*
wsl nasm -felf32 boot.asm -o obj/boot.o
wsl gcc -ffreestanding -nostdlib -mno-red-zone -fno-pie -fno-exceptions -m32 -c src/*.c -o obj/kernel.o
wsl ld -m elf_i386 -T link.ld -o bin/kernel.bin obj/*.o
qemu-system-i386 -fda bin/kernel.bin