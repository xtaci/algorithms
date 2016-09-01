#ifndef ALGO_GB18030_H__
#define ALGO_GB18030_H__

/**
 * Read from the string encoded in GB18030 into WORD
 * return the length of the WORD
 */
static inline short 
gb18030_read(const char * str, int start, uint32_t * WORD)
{
	unsigned char * w = (unsigned char *)&str[start];

	if (w[0] <= 0x7F) {	// 1-byte
		*WORD = w[0];
		return 1;
	} else if (w[0] >= 0x81 && w[0] <=0xFE) {
		if (w[1] >=0x40 && w[1] <=0xFE) {	// 2-byte
			*WORD = (w[0] << 8) | w[1];
			return 2;
		} else {	// 4-byte
			*WORD = (w[0]<<24)|(w[1]<< 16)|(w[2]<<8)|w[3];
			return 4;
		}
	}
	return 0;
}

/**
 * print a gb18030 char
 */
static inline void 
gb18030_putchar(const uint32_t w)
{
	union _decomposer{
		struct{
			unsigned char w3;
			unsigned char w2;
			unsigned char w1;
			unsigned char w0;
		} dtls;
		uint32_t word;
	};
	_decomposer t;
	t.word = w;
	unsigned char w0 = t.dtls.w0;
	unsigned char w1 = t.dtls.w1;
	unsigned char w2 = t.dtls.w2;
	unsigned char w3 = t.dtls.w3;
	
	if (w0) {
		putchar(w0);putchar(w1);putchar(w2);putchar(w3);		
	} else if (w2) {
		putchar(w2);putchar(w3);
	} else {
		putchar(w3);
	}
}

#endif //
