#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "update_struct.h"

#define DATA_SIZE       0x1000000
#define UBOOT_START     0x0
#define BOOT_DATA_START 0x30000
#define USER_DATA_START 0x50000
#define KERNEL_START    0x70000
#define ROOTFS_START    0x350000
int main(int argc, char *argv[])
{
    FILE *fin_uboot, *fin_boot_data, *fin_user_data, *fin_uImage, *fin_rootfs, *fout_boot;
    char *data = NULL;
    int len = 0;
	fin_uboot = fopen("uboot", "rb+");
	if (NULL == fin_uboot) {
		printf("open file_in uboot error!\n");
        goto err0;
	}
	fin_boot_data = fopen("boot_data.bin", "rb+");
	if (NULL == fin_boot_data) {
		printf("open file_in boot_data.bin error!\n");
        goto err1;
	}
	fin_user_data = fopen("user_data.bin", "rb+");
	if (NULL == fin_user_data) {
		printf("open file_in user_data.bin error!\n");
        goto err2;
	}
	fin_uImage = fopen("uImage", "rb+");
	if (NULL == fin_uImage) {
		printf("open file_in uImage error!\n");
        goto err3;
	}
	fin_rootfs = fopen("rootfs.sfs", "rb+");
	if (NULL == fin_rootfs) {
		printf("open file_in rootfs error!\n");
        goto err4;
	}
	fout_boot = fopen("../out/16Mboot.bin", "wb+");
	if (NULL == fout_boot) {
		printf("open file_in 16Mboot.bin error!\n");
        goto err5;
	}
    data = malloc(DATA_SIZE);
    if (NULL == data) {
        printf("malloc 0x%x failed.\n", DATA_SIZE);
        goto err6;
	}
    memset(data, 0xff, DATA_SIZE);

	fseek(fin_uboot, 0 , SEEK_END);
	len = ftell(fin_uboot);
	fseek(fin_uboot, 0 , SEEK_SET);
    fread(data + UBOOT_START, len, 1, fin_uboot);

	fseek(fin_boot_data, 0 , SEEK_END);
	len = ftell(fin_boot_data);
	fseek(fin_boot_data, 0 , SEEK_SET);
    fread(data + BOOT_DATA_START, len, 1, fin_boot_data);

	fseek(fin_user_data, 0 , SEEK_END);
	len = ftell(fin_user_data);
	fseek(fin_user_data, 0 , SEEK_SET);
    fread(data + USER_DATA_START, len, 1, fin_user_data);

	fseek(fin_uImage, 0 , SEEK_END);
	len = ftell(fin_uImage);
	fseek(fin_uImage, 0 , SEEK_SET);
    fread(data + KERNEL_START, len, 1, fin_uImage);

	fseek(fin_rootfs, 0 , SEEK_END);
	len = ftell(fin_rootfs);
	fseek(fin_rootfs, 0 , SEEK_SET);
    fread(data + ROOTFS_START, len, 1, fin_rootfs);

	fwrite(data, DATA_SIZE, 1, fout_boot);

err6:
    free(data);
err5:
    fclose(fout_boot);
err4:
    fclose(fin_rootfs);
err3:
    fclose(fin_uImage);
err2:
    fclose(fin_user_data);
err1:
    fclose(fin_boot_data);
err0:
    fclose(fin_uboot);
    return 0;
}
