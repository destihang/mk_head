#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "update_struct.h"

int main(int argc, char* argv[])
{
    FILE *fin, *fout;
	int size_in;
	char *data_in = NULL;
	struct boot_data_info boot;

	fin= fopen("boot_data.bin", "rb+");
	if (NULL == fin) {
		printf("open file_in %s error!\n", "boot_data.bin");
		return -1;
	}
	memset(&boot, 0, sizeof(struct boot_data_info));
	fread(&boot, sizeof(struct boot_data_info), 1, fin);
    printf("magic:0x%x, count:%d, checksum:%d, last_boot_method:%d, kernel_stat:%d, rootfs_stat:%d, resv:%d\n",
            boot.magic, boot.count, boot.checksum, boot.last_boot_method, boot.kernel_stat, boot.rootfs_stat, boot.resv);
	fclose(fin);
	return 0;
}
