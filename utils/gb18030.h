#ifndef __GB18030_H__
#define __GB18030_H__

/**
 * Read from the string encoded in GB18030 into WORD
 * return the length of the WORD
 */
inline short gb18030_read(const char * str, int start, uint32_t * WORD)
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
inline void gb18030_putchar(const uint32_t WORD)
{
	unsigned char w0 = (WORD&0xFF000000)>>24;
	unsigned char w1 = (WORD&0xFF0000)>>16;
	unsigned char w2 = (WORD&0xFF00)>>8;
	unsigned char w3 = WORD&0xFF;
	
	if (w0) {
		putchar(w0);putchar(w1);putchar(w2);putchar(w3);		
	} else if (w2) {
		putchar(w2);putchar(w3);
	} else {
		putchar(w3);
	}
}

#endif //
