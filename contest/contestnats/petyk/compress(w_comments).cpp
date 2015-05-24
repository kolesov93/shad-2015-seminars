#include<stdio.h>
#include<stdlib.h>

const int MAX_LENGTH = 17;

unsigned long DataCompare(unsigned char *str1, unsigned char *str2, unsigned long maxlength) {
	//функция для нахождения максимального общего префикса двух строк
	unsigned long length = 1;
	for(; *str1 == *str2 && length < maxlength; length++, str1++, str2++);	
	return length;
}

unsigned char *SearchForPhrase(unsigned char *str, unsigned char *src, unsigned long maxlength, unsigned long *bestlength) {
	//функция для поиска максимальной строки, совпадающей с [str, str+1, ...]
	//в окне [src, ..., str], длины не больше maxlength
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
	unsigned char control = 0; //вектор из {0,1}^8. 0, если на соответствующей позиции стоит просто символ; 1, если код
	control_ptr = dest; //место записи control
	dest++;
	while(p <= src_end && dest <= dest_end) {
		//обрабаытваем счетчик control, так как работаем по восьмеркам
		control_counter++;
		if(control_counter == 9) {
				*control_ptr = control;
				control_ptr = dest;
				dest++;
				control = 0;
				control_counter=1;
		}
		//вычисляем максимальную длину кодируемых фраз
		//максимум из длины оставшегося текста, ширины окна, и заданной константы
		//в данном случае кодируем длины от 2 до 17, чтобы уместить длину в 4 бита
		maxlength = (unsigned long)(src_end - src);
		if(maxlength > windowsize) 
			maxlength = windowsize;
		if(maxlength > MAX_LENGTH) 
			maxlength = MAX_LENGTH;
		temp = p - windowsize; //указатель на левую часть окна
		if(temp < src)
			temp = src;
		if(!phrase_ptr)
			phrase_ptr = SearchForPhrase(p, temp, maxlength, &phrase_length);
		if(maxlength > 1)
			lazy_ptr = SearchForPhrase((p+1), (temp+1), maxlength--, &lazy_length);
		//не кодируем текущий символ
		if((lazy_ptr && lazy_length > phrase_length) || !phrase_ptr || !maxlength) {
			phrase_ptr = lazy_ptr;
			phrase_length = lazy_length;
			control <<= 1;
			control |= 0;
			*dest = *p;
			dest++;
			p++;
		}
		//кодируем найденную последовательность
		else {
			//добавляем в вектор control 1
			control <<= 1;
			control |= 1;
			//считаем смещение и записываем его в первые 12 битов
			phrase_index = (unsigned short)(p - phrase_ptr);
			phrase_index = phrase_index<<4;
			//записываем длину в последние 4 бита
			phrase_index = phrase_index | (((unsigned short)phrase_length - 2)&0x0f);
			//записываем биты по восьмеркам
			*dest = (phrase_index>>8);
			dest++;
			*dest = (phrase_index&0xff);
			dest++;
			p += phrase_length;
			phrase_ptr = NULL;
		}
	}
	//завершаем кодовым словом [0|0]
	control_counter++;
	control <<= 1;
	control |= 1;
	*dest = 0;
	dest++;
	*dest = 0;
	dest++;
	//добиваем до 8 битов и записываем
	while(control_counter != 8) {
		control <<= 1;
		control_counter++;
	}
	*control_ptr = control;
	//возвращем длину сжатого текста
	return (unsigned long)(dest - start_dest);
}

int main(int argc, char **argv) {
	FILE *in, *out;
	unsigned long newsize = 0;
	fpos_t filesize = 0;
	void *srcmem, *destmem;

	fopen_s(&in, argv[1], "rb");
	fopen_s(&out, argv[2], "wb");
	//узнаем размер исходного текста
	fseek(in, 0, SEEK_END);
	fgetpos(in, &filesize);
	fseek(in, 0, SEEK_SET);	
	//выделяем память
	srcmem = malloc((size_t)filesize);
	destmem = malloc((size_t)filesize);
	//считываем текст в scrmem
	fread(srcmem, 1, (size_t)filesize, in);
	//записываем в вывод длину исходного текста
	fwrite((void *)&filesize, 1, 4, out);
	//сжимаем текст и записываем его
	newsize = CompressData((unsigned char *)srcmem, (unsigned char *)destmem, (unsigned long)filesize, 0xfff);						
	fwrite(destmem, 1, (size_t)newsize, out);

	//освобождаем память, закрываем файлы
	free(srcmem);
	free(destmem);
	fclose(in);
	fclose(out);
	return 0;
}