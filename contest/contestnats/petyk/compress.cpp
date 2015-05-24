#include<stdio.h>
#include<stdlib.h>

const int MAX_LENGTH = 17;

unsigned long DataCompare(unsigned char *str1, unsigned char *str2, unsigned long maxlength) {
	unsigned long length = 1;
	for(; *str1 == *str2 && length < maxlength; length++, str1++, str2++);
	return length;
}

unsigned char *SearchForPhrase(unsigned char *str, unsigned char *src, unsigned long maxlength, unsigned long *bestlength) {
	unsigned char *p = str, *best = NULL;
	unsigned long curlength;
	*bestlength = 1;
	p--;
	while(p >= src) {
		if(*p == *str) {
			curlength = DataCompare((p + 1), (str + 1), maxlength);
			if(curlength > *bestlength) {
				*bestlength = curlength;
				best = p;
			}
		}
		p--;
	}
	return best;
}

unsigned long CompressData(unsigned char *src,
						   unsigned char *dest,
						   unsigned long src_length,
						   unsigned long windowsize) {
	unsigned char *src_end = src + src_length,
		*dest_end = dest + src_length,
		*phrase_ptr = NULL,
		*lazy_ptr = NULL,
		*control_ptr,
		*start_dest = dest,
		*temp,
		*p = src;
	unsigned long phrase_length,
				  maxlength,
				  lazy_length,
				  control_counter = 0,
				  iterationcnt = 0;
	unsigned short phrase_index;
	unsigned char control = 0;
	control_ptr = dest;
	dest++;
	while(p <= src_end && dest <= dest_end) {
		control_counter++;
		if(control_counter == 9) {
				*control_ptr = control;
				control_ptr = dest;
				dest++;
				control = 0;
				control_counter=1;
		}
		maxlength = (unsigned long)(src_end - src);
		if(maxlength > windowsize)
			maxlength = windowsize;
		if(maxlength > MAX_LENGTH)
			maxlength = MAX_LENGTH;
		temp = p - windowsize;
		if(temp < src)
			temp = src;
		if(!phrase_ptr)
			phrase_ptr = SearchForPhrase(p, temp, maxlength, &phrase_length);
		if(maxlength > 1)
			lazy_ptr = SearchForPhrase((p+1), (temp+1), maxlength--, &lazy_length);
		if((lazy_ptr && lazy_length > phrase_length) || !phrase_ptr || !maxlength) {
			phrase_ptr = lazy_ptr;
			phrase_length = lazy_length;
			control <<= 1;
			control |= 0;
			*dest = *p;
			dest++;
			p++;
		}
		else {
			control <<= 1;
			control |= 1;
			phrase_index = (unsigned short)(p - phrase_ptr);
			phrase_index = phrase_index<<4;
			phrase_index = phrase_index | (((unsigned short)phrase_length - 2)&0x0f);
			*dest = (phrase_index>>8);
			dest++;
			*dest = (phrase_index&0xff);
			dest++;
			p += phrase_length;
			phrase_ptr = NULL;
		}
	}
	control_counter++;
	control <<= 1;
	control |= 1;
	*dest = 0;
	dest++;
	*dest = 0;
	dest++;
	while(control_counter != 8) {
		control <<= 1;
		control_counter++;
	}
	*control_ptr = control;
	return (unsigned long)(dest - start_dest);
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
	srcmem = malloc((size_t)filesize.__pos);
	destmem = malloc((size_t)filesize.__pos);
	fread(srcmem, 1, (size_t)filesize.__pos, in);
	fwrite((void *)&filesize, 1, 4, out);
	newsize = CompressData((unsigned char *)srcmem, (unsigned char *)destmem, (unsigned long)filesize.__pos, 0xfff);
	fwrite(destmem, 1, (size_t)newsize, out);

	free(srcmem);
	free(destmem);
	fclose(in);
	fclose(out);
	return 0;
}
