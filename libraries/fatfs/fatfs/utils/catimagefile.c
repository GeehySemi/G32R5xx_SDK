/*
 * ======== catimagefile.c ========
 *
 * print out the contents of a text file [FILE] that exists on a RAM disk
 * image.
 *
 * Usage:
 *
 *     catimagefile [RAM-disk-filename] [file]
 *
 *     RAM-disk-filename: name of an existing RAM disk image file (usually
 *                        created with 'mkimage' utility).
 *
 *     file: name of a file to cat that exists on the RAM disk image file
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
int main(int argc, char *argv[])
{
    unsigned int   size = 0;
    unsigned char *diskBuf;
    char          *filename;
    FRESULT        result;
    char          *ramImageName;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s ram-file-name [file.txt]\n", argv[0]);
        exit(1);
    }

    ramImageName = argv[1];
    filename = argv[2];

    /* create and mount RAM disk from existing image file */
    if ((diskBuf = loadRamImage(ramImageName, &size)) == NULL) {
        fprintf(stderr, "ERROR: could not load RAM disk image \'%s\'.\n",
                ramImageName);
        exit(1);
    }

    if ((result = catTextFile(filename)) != FR_OK) {
         printf("ERROR printing text file: returned: %d\n", result);
         exit(1);
    }

    /* un-register the RAM disk drive */
    if ((result = f_mount(0, NULL)) != FR_OK) {
        fprintf(stderr, "ERROR: un-mounting drive failed: %d\n", result);
        exit(1);
    }

    return 0;
}
