#include<stdio.h>
#include<stdlib.h>

unsigned long Decompress(unsigned char *src, unsigned char *dest) {
	unsigned char control;
	unsigned int phrase_index, control_count = 0;
	int phrase_length = 0;
	unsigned char *dest_start = dest, *temp;
	unsigned short codeword = 0;
	control = *src;
	src++;
	while(1) {
		if((control>>7) == 0) {
			*dest = *src;
			dest++;
			src++;
		}
		else {
			codeword = *src;
			codeword <<= 8;
			codeword |= *(src+1);
			phrase_index = codeword>>4;
			if(!phrase_index)
				break;
			temp = dest - phrase_index;

			for(phrase_length = ((codeword&0x0f)+2);
				phrase_length > 0;
				phrase_length--,temp++,dest++) {
					*dest=*temp;
			}
			src += 2;
		}
		control = control<<1;
		control_count++;
		if(control_count >= 8) {
			control =* src;
			*src++;
			control_count = 0;
		}
	}
	return (unsigned long)(dest - dest_start) - 1;
}

int main(int argc, char **argv) {
	FILE *in, *out;
	unsigned long newsize = 0;
	fpos_t filesize;
	void *srcmem, *destmem;

    in = stdin;
    out = stdout;
	fseek(in, 0, SEEK_END);
	fgetpos(in, &filesize);
	fseek(in, 0, SEEK_SET);
	fread((void *)&newsize, 1, 4, in);
	destmem = malloc((size_t)newsize + 1);
	srcmem = malloc((size_t)filesize.__pos);
	fread(srcmem, 1, (size_t)filesize.__pos - 4, in);
	newsize = Decompress((unsigned char *)srcmem, (unsigned char *)destmem);
	fwrite(destmem, 1, (size_t)newsize, out);

	free(srcmem);
	free(destmem);
	fclose(in);
	fclose(out);
	return 0;
}
