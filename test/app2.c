

#include "ff.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdint.h>

#include "fatfs_sdram.h"

/* FATFS related */
FATFS fs;
FIL fil;
FRESULT fres;
uint8_t SD_Buffer[15];

uint64_t working_buff[1024];

DISKIO_LowLevelDriver_t RamDriver = {
TM_FATFS_SDRAM_disk_initialize,
TM_FATFS_SDRAM_disk_status,
TM_FATFS_SDRAM_disk_ioctl,
TM_FATFS_SDRAM_disk_write,
TM_FATFS_SDRAM_disk_read,
};

int main(void) {

    disk_setup_driver("SDRAM", &RamDriver);

    /* Mount FATFS on SDRAM */
	fres = f_mount(&fs, "SDRAM:", 0);
	
	/* Create FAT volume with default cluster size, IMPORTANT for SDRAM because content is not stored forever! */
	/* This has to be done only once, when you first time init your SDRAM */
	/* It is initialized first time using f_mount() function call above */
	fres = f_mkfs("SDRAM:", NULL, working_buff, sizeof(working_buff));
	
	/* Open file */
	fres = f_open(&fil, "SDRAM:test.txt", FA_CREATE_ALWAYS | FA_READ | FA_WRITE);
	
	/* Write data */
    UINT n_wrote;
    fres = f_write(&fil, "Hello world", 11, &n_wrote);
	
	/* Close file */
	fres = f_close(&fil);
	
	/* Unmount */
	f_mount(NULL, "SDRAM:", 1);
	
	/* If everything succedded */
	if (fres == FR_OK) {
		/* Mount FATFS on SDRAM */
		fres = f_mount(&fs, "SDRAM:", 0);
		
		/* No need to call MKFS here again because fat system is already on SDRAM */
		
		/* Open file */
		fres = f_open(&fil, "SDRAM:test.txt", FA_READ | FA_WRITE);
		
		/* Read data */
        UINT n_read;
        fres = f_read(&fil, SD_Buffer, 11, &n_read);
		
		/* Close file */
		fres = f_close(&fil);
		
		/* Unmount SDRAM */
		f_mount(NULL, "SDRAM:", 1);
		
		/* Turn on LED GREEN */
		if (strncmp((char *)SD_Buffer, "Hello world", 11) == 0) {
			/* Turn on GREEN led */
            puts("LED_GREEN");
        } else {
			/* Red led */
            puts("LED_RED");
		}
	} else {
		/* Red led */
        puts("LED_RED");
	}
	

}
