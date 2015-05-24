//Алгоритм расжатия данных LZSS

#include<stdio.h>
#include<stdlib.h>

unsigned long Decompress(unsigned char *src, unsigned char *dest) {
	unsigned char control; ////вектор из {0,1}^8. 0, если на соответствующей позиции стоит просто символ; 1, если код
	unsigned int phrase_index, control_count = 0;
	int phrase_length = 0;
	unsigned char *dest_start = dest, *temp;
	unsigned short codeword = 0;	
	control = *src;
	src++;
	while(1) {				
		if((control>>7) == 0) { //если символ не является кодом, то просто переносим его			
			*dest = *src;
			dest++;
			src++;
		}		
		else {
			//считываем первые 8 битов
			codeword = *src;
			codeword <<= 8;
			//считываем и дописываем вторые 8 битов
			codeword |= *(src+1);
			//вычисляем смещение как первые 12 битов
			phrase_index = codeword>>4;
			if(!phrase_index)
				break;
			//указатель на начало последовательности, которая повторилась
			//и которую во второй раз мы закодироваи
			temp = dest - phrase_index;

			for(phrase_length = ((codeword&0x0f)+2); //считаем длину как последние 4 бита +2
				phrase_length > 0;
				phrase_length--,temp++,dest++) {
					*dest=*temp;					//переписываем эту последовательность заданной длины
			}
			//переходим на две восьмерки битов дальше, так как считали их
			src += 2;
		}
		//удаляем из вектора control первый элемент, так как обработали его
		control = control<<1;
		//следим за счетчиком, так как работаем по восмьеркам
		control_count++;
		if(control_count >= 8) {
			control =* src;
			*src++;
			control_count = 0;
		}
	}
	//возвращаем длину расжатого текста
	return (unsigned long)(dest - dest_start) - 1;
}

int main(int argc, char **argv) {
	FILE *in, *out;
	unsigned long newsize = 0;
	fpos_t filesize = 0;
	void *srcmem, *destmem;

	fopen_s(&in, argv[1], "rb");
	fopen_s(&out, argv[2], "wb");
	//узнаем размер исходного(сжатого) текста
	fseek(in, 0, SEEK_END);
	fgetpos(in, &filesize);
	fseek(in, 0, SEEK_SET);
	//считываем размер несжатого текста, который мы туда записали
	fread((void *)&newsize, 1, 4, in);
	//выделяем память
	destmem = malloc((size_t)newsize + 1);
	srcmem = malloc((size_t)filesize);
	//считываем сжатый текст в srcmem
	fread(srcmem, 1, (size_t)filesize - 4, in);
	//расжимаем текст, записываем его в destmem
	newsize = Decompress((unsigned char *)srcmem, (unsigned char *)destmem);
	fwrite(destmem, 1, (size_t)newsize, out);

	//освобождаем память, закрываем файлы
	free(srcmem);
	free(destmem);
	fclose(in);
	fclose(out);
	return 0;
}