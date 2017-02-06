CC=gcc
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %, $(SRC))
KERNEL_IN=../in/uImage
ROOTFS_IN=../in/rootfs.sfs
UBOOT_IN=../in/uboot
BOOT_DATA_OUT=../in/boot_data.bin
USER_DATA_OUT=../in/user_data.bin
KERNEL_OUT=../out/uImage-out
ROOTFS_OUT=../out/rootfs.sfs-out
BIN_OUT=../out/16Mboot.bin

%.o:%.c
	$(CC) -c $@
%:%.o
	$(CC) -o $@
all:$(OBJ) $(KERNEL_OUT) $(ROOTFS_OUT) $(BOOT_DATA_OUT) $(USER_DATA_OUT)

$(KERNEL_OUT):
	./add_part_head_info $(KERNEL_IN) $(KERNEL_OUT)

$(ROOTFS_OUT):
	./add_part_head_info $(ROOTFS_IN) $(ROOTFS_OUT)

$(BOOT_DATA_OUT):
	./produce_uboot_data_parts_info

$(USER_DATA_OUT):
	./produce_user_data_parts_info

#$(BIN_OUT):
#./produce_16M_data $(UBOOT_IN) $(BOOT_DATA_OUT) $(USER_DATA_OUT) $(KERNEL_IN) $(ROOTFS_IN) $(BIN_OUT)

clean:
	rm -rf $(OBJ) $(KERNEL_OUT) $(ROOTFS_OUT) $(BOOT_DATA_OUT) $(USER_DATA_OUT) $(BIN_OUT)
