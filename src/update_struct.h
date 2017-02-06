#define UPDATE_PART_NULL    0
#define UPDATE_PART_KERNEL  1
#define UPDATE_PART_ROOTFS  2

#define STAT_OK             0
#define STAT_IN_SEC_SYS     1
#define STAT_IN_BACKUP      2

#define UPDATE_FD_1 1
#define UPDATE_FD_2 2

struct part_head_table {
	int magic;
	int part_type;
};

struct part_head_info {
	int	magic;
	int len;
	int checksum;
};

struct boot_data_info {
	int magic;
	int count;
	int checksum;
    int backup_len;
	char last_boot_method;
	char kernel_stat;
	char rootfs_stat;
	char resv;
};

struct user_data_head {
	int magic;
	int count;
	int checksum;
};

struct user_data_rom {
	int val1;
	int val2;
	int val3;
	int val4;
	char val5[64];
};

struct user_data_ram {
	int val1;
	int val2;
	int val3;
	int val4;
	char val5[64];
};
