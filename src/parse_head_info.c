#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "update_struct.h"

static int _calculate_checksum(unsigned short *data, int data_len)
{
    int checksum = 0;
    int i = 0;

    if ( data == NULL || data_len <= 0 )
    	return -1;

    for ( ; i < data_len; i++ )
    	checksum += data[i] & 0xff;

    return checksum;
}

int main(int argc, char* argv[])
{
    FILE *fin, *fout;
	int size_in;
	char *data_in = NULL;
	struct part_head_info head;

	if (argc != 3) {
		printf(" usage [add_part_head_info file_int file_out]\n");
		return -1;
	}

	fin= fopen(argv[1], "rb+");
	if (NULL == fin) {
		printf("open file_in %s error!\n", argv[1]);
		return -1;
	}
	fseek(fin, 0 , SEEK_END);
	size_in = ftell(fin);
	fseek(fin, 0 , SEEK_SET);
	data_in = malloc(size_in);
	if (NULL == data_in) {
		printf("malloc %d size falied!\n", size_in);
		fclose(fin);
		return -1;
	}
	fread(data_in, size_in, 1, fin);
	fclose(fin);

	memset(&head, 0, sizeof(struct part_head_info));
	head.magic = 0x6138;
	head.checksum = _calculate_checksum(data_in, size_in);
printf("magic:0x%x, checsum:0x%x\n", head.magic, head.checksum);
	fout= fopen(argv[2], "w+");
	if (NULL == fout) {
		printf("open file_out %s error!\n", argv[2]);
		return -1;
	}
	fwrite(&head, sizeof(struct part_head_info), 1, fout);
	fwrite(data_in, size_in, 1, fout);
	free(data_in);
	fclose(fout);
	return 0;
}
