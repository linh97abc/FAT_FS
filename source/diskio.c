/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "ff.h"
#include "diskio.h"		/* FatFs lower layer API */
#include <stdint.h>
#include <string.h>


/* Make driver structure */
static DISKIO_LowLevelDriver_t FATFS_LowLevelDrivers[FF_VOLUMES] = { 0 };

static const char *const diskVolumeStr[FF_VOLUMES] = {FF_VOLUME_STRS};

DRESULT disk_setup_driver(const char *path, DISKIO_LowLevelDriver_t* Driver)
{
	BYTE pdrv;
	BYTE isPathValid = 0;

	for (pdrv = 0; pdrv < FF_VOLUMES; pdrv++)
	{
		// strncmp(path, )

		if (strcmp(path, diskVolumeStr[pdrv]) == 0)
		{
			isPathValid = 1;
			break;
		}
	}

	if (!isPathValid)
	{
		return RES_PARERR;
	}
	

	/* Add to structure */
	FATFS_LowLevelDrivers[pdrv].disk_initialize = Driver->disk_initialize;
	FATFS_LowLevelDrivers[pdrv].disk_status = Driver->disk_status;
	FATFS_LowLevelDrivers[pdrv].disk_ioctl = Driver->disk_ioctl;
	FATFS_LowLevelDrivers[pdrv].disk_read = Driver->disk_read;
	FATFS_LowLevelDrivers[pdrv].disk_write = Driver->disk_write;

	return RES_OK;
}


/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
	/* Return low level status */
	if (FATFS_LowLevelDrivers[pdrv].disk_initialize) {

		return FATFS_LowLevelDrivers[pdrv].disk_initialize();
	}
	
	/* Return parameter error */
	return RES_PARERR;
}

/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
	/* Return low level status */
	if (FATFS_LowLevelDrivers[pdrv].disk_status) {
		return FATFS_LowLevelDrivers[pdrv].disk_status();
	}
	
	/* Return parameter error */
	return RES_PARERR;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	UINT count		/* Number of sectors to read (1..128) */
)
{
	/* Check count */
	if (!count) {
		return RES_PARERR;
	}
	
	/* Return low level status */
	if (FATFS_LowLevelDrivers[pdrv].disk_read) {
		return FATFS_LowLevelDrivers[pdrv].disk_read(buff, sector, count);
	}
	
	/* Return parameter error */
	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
#if FF_FS_READONLY == 0
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	UINT count			/* Number of sectors to write (1..128) */
)
{
	/* Check count */
	if (!count) {
		return RES_PARERR;
	}
	
	/* Return low level status */
	if (FATFS_LowLevelDrivers[pdrv].disk_write) {
		return FATFS_LowLevelDrivers[pdrv].disk_write(buff, sector, count);
	}
	
	/* Return parameter error */
	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	/* Return low level status */
	if (FATFS_LowLevelDrivers[pdrv].disk_ioctl) {
		return FATFS_LowLevelDrivers[pdrv].disk_ioctl(cmd, buff);
	}
	
	/* Return parameter error */
	return RES_PARERR;
}
