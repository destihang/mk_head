#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "update_struct.h"

#define DATA_PART_SIZE 0x10000
int main(int argc, char *argv[])
{
    FILE *fout;
    char *data_part = NULL;
    int len = sizeof(struct user_data_head)+sizeof(struct user_data_rom)+sizeof(struct user_data_ram);
    struct user_data_head *data_head = NULL;
    struct user_data_rom *data_rom = NULL;
    struct user_data_ram *data_ram = NULL;
    int i;
	fout= fopen("user_data.bin", "wb+");
	if (NULL == fout) {
		printf("open file_in boot_data.bin error!\n");
		return -1;
	}

    data_part = malloc(DATA_PART_SIZE);
    memset(data_part, 0, DATA_PART_SIZE);

    data_head = (struct user_data_head*)data_part;
    data_head->magic = 0x6138;
    data_head->count = 1;
    data_head->checksum = 0;

    data_rom = (struct user_data_rom*)(data_part+sizeof(struct user_data_head));
    data_rom->val1 = 8888;
    data_rom->val2 = 8888;
    data_rom->val3 = 8888;
    data_rom->val4 = 8888;

    data_ram = (struct user_data_ram*)(data_part+sizeof(struct user_data_head)+sizeof(struct user_data_rom));
    data_ram->val1 = 8888;
    data_ram->val2 = 8888;
    data_ram->val3 = 8888;
    data_ram->val4 = 8888;

    for (i=sizeof(struct user_data_head); i<len; ++i)
        data_head->checksum += data_part[i] & 0xff;
printf("part1 magic:0x%x, checksum:%d, count:%d\n", data_head->magic, data_head->checksum, data_head->count);
	fwrite(data_part, DATA_PART_SIZE, 1, fout);

#if 1
    memset(data_part, 0, DATA_PART_SIZE);

    data_head = (struct user_data_head*)data_part;
    data_head->magic = 0x6138;
    data_head->count = 0;
    data_head->checksum = 0;

    data_rom = (struct user_data_rom*)(data_part+sizeof(struct user_data_head));
    data_rom->val1 = 8888;
    data_rom->val2 = 8888;
    data_rom->val3 = 8888;
    data_rom->val4 = 8888;

    data_ram = (struct user_data_ram*)(data_part+sizeof(struct user_data_head)+sizeof(struct user_data_rom));
    data_ram->val1 = 8888;
    data_ram->val1 = 8888;
    data_ram->val2 = 8888;
    data_ram->val3 = 8888;
    data_ram->val4 = 8888;

    for (i=sizeof(struct user_data_head); i<len; ++i)
        data_head->checksum += data_part[i] & 0xff;
printf("part2 magic:0x%x, checksum:%d, count:%d\n", data_head->magic, data_head->checksum, data_head->count);
	fwrite(data_part, DATA_PART_SIZE, 1, fout);
#endif

    free(data_part);
    fclose(fout);
    return 0;
}
