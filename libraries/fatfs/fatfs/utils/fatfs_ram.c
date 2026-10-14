/*
 * ======== fatfs_ram.c ========
 * Simple RAM disk layer for FatFs.
 *
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <diskio.h>

#define SECTORSIZE 512

static unsigned char * diskMem = NULL;
static unsigned numSectors = 0;

extern int32_t fatfs_getFatTime(void);

void ramdisk_init(unsigned char * data, int numBytes)
{
    diskMem = data;
    numSectors = numBytes / SECTORSIZE;
}

DSTATUS disk_initialize(BYTE drive)
{
    assert(drive == 0);

    return (0);
}

DSTATUS disk_status(BYTE drive)
{
    assert(drive == 0);

    return (0);
}

DRESULT disk_read(BYTE drive, BYTE * buf, DWORD start, BYTE num)
{
    assert(drive == 0);

    memcpy(buf, diskMem + start * SECTORSIZE, num * SECTORSIZE);

    return (RES_OK);
}

#if     _READONLY == 0
DRESULT disk_write(BYTE drive, const BYTE * buf, DWORD start, BYTE num)
{
    assert(drive == 0);

    memcpy(diskMem + start * SECTORSIZE, buf, num * SECTORSIZE);

    return (RES_OK);
}
#endif

DRESULT disk_ioctl(BYTE drive, BYTE cmd, void * buf)
{
    DRESULT result;

    assert(drive == 0);

    switch (cmd) {
        case CTRL_SYNC:
            result = RES_OK;
            break;

        case GET_BLOCK_SIZE:
        case CTRL_ERASE_SECTOR:
            result = RES_PARERR;
            break;

        case GET_SECTOR_SIZE:
            *(WORD *)buf = SECTORSIZE;
            result = RES_OK;
            break;

        case GET_SECTOR_COUNT:
            *(DWORD *)buf = numSectors;
            result = RES_OK;
            break;

        default:
            result = RES_ERROR;
            break;
    }

    return (result);
}

DWORD get_fattime(void)
{
    /* call TI dummy implementation or user defined hook function */
    return (fatfs_getFatTime());
}
