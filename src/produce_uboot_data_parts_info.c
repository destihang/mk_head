#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "update_struct.h"

#define DATA_PART_SIZE 0x10000
int main(int argc, char *argv[])
{
    FILE *fout;
    int i;
    char *data_part = NULL;
    struct boot_data_info *data_info_1, *data_info_2;
	fout= fopen("boot_data.bin", "wb+");
	if (NULL == fout) {
		printf("open file_in boot_data.bin error!\n");
		return -1;
	}

    data_part = malloc(DATA_PART_SIZE);
    memset(data_part, 0, DATA_PART_SIZE);
    data_info_1 = (struct boot_data_info*)data_part;
    data_info_1->magic = 0x6138;
    data_info_1->count = 1;
    data_info_1->last_boot_method = 0;
    data_info_1->kernel_stat = STAT_OK;
    data_info_1->rootfs_stat = STAT_OK;
    data_info_1->resv = 0;
    data_info_1->backup_len = 0;
    data_info_1->checksum = 0;
    for (i=12; i<sizeof(struct boot_data_info); ++i)
        data_info_1->checksum += data_part[i] & 0xff;
printf("kernel_stat:%d, rootfs_stat:%d, checksum:%d\n", data_info_1->kernel_stat, data_info_1->rootfs_stat, data_info_1->checksum);
	fwrite(data_part, DATA_PART_SIZE, 1, fout);

#if 1
    memset(data_part, 0, DATA_PART_SIZE);
    data_info_2 = (struct boot_data_info*)data_part;
    data_info_2->magic = 0x6138;
    data_info_2->count = 0;
    data_info_2->last_boot_method = 0;
    data_info_2->kernel_stat = STAT_OK;
    data_info_2->rootfs_stat = STAT_OK;
    data_info_2->resv = 0;
    data_info_2->backup_len = 0;
    data_info_2->checksum = 0;
    for (i=12; i<sizeof(struct boot_data_info); ++i)
        data_info_2->checksum += data_part[i] & 0xff;
printf("kernel_stat:%d, rootfs_stat:%d, checksum:%d\n", data_info_2->kernel_stat, data_info_2->rootfs_stat, data_info_2->checksum);
	fwrite(data_part, DATA_PART_SIZE, 1, fout);
#endif

    free(data_part);
    fclose(fout);
    return 0;
}
