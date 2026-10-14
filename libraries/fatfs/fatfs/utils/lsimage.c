/*
 * ======== lsimage.c ========
 *
 * print out the files and directories on a RAM disk image.
 *
 * Usage:
 *
 *     lsimage [RAM-disk-filename]
 *
 *     RAM-disk-filename: name of an existing RAM disk image file (usually
 *                        created with 'mkimage' utility).
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <ff.h>
#include <fsutils.h>

extern void ramdisk_init(void *, int);

/*
 *  ======== main ========
 */
int main(int argc, char * argv[])
{
    unsigned int size = 0;
    unsigned char * diskBuf;
    FRESULT result;
    char * ramImageName;
    char path[128];

    path[0] = '/';
    path[1] = '\0';

    if (argc < 2) {
        fprintf(stderr, "Usage: %s ram-file-name\n", argv[0]);
        exit(1);
    }

    ramImageName = argv[1];

    /* create and mount RAM disk from existing image file */
    if ((diskBuf = loadRamImage(ramImageName, &size)) == NULL) {
        fprintf(stderr, "ERROR: could not load RAM disk image \'%s\'.\n",
                ramImageName);
        exit(1);
    }

    if ((result = scanFiles(path)) != FR_OK) {
         printf("ERROR scanning files and directories: returned: %d\n", result);
         exit(1);
    }

    /* un-register the RAM disk drive */
    if ((result = f_mount(0, NULL)) != FR_OK) {
        fprintf(stderr, "ERROR: un-mounting drive failed: %d\n", result);
        exit(1);
    }

    return 0;
}
