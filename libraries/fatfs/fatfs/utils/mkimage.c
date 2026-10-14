/*
 * ======== mkimage.c ========
 *
 * Utility to create a RAM disk image using the FatFs file system.  The disk
 * image is saved into a binary file that is stored onto the local hard drive.
 *
 * Once the image has been created, it can be manipulated using the other FatFs
 * utilities that are available (e.g. adding files or directories to the image).
 *
 * Usage:
 *
 *     mkimage [filename] [size]
 *
 *     filename: name of the binary file to store the RAM disk image.  This file
 *               will be stored on the local hard drive.  If the file already
 *               exists, it will be overwritten.
 *
 *     size:     size of the RAM disk to create.
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
    unsigned int size = 0;
    unsigned char *diskBuf;
    FRESULT result;
    char *fileName;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s [FILENAME] [SIZE]\n", argv[0]);
        fprintf(stderr, "\tCreate RAM disk image of size [SIZE] and output to");
        fprintf(stderr, " binary file [FILENAME]\n");
        exit(1);
    }

    fileName = argv[1];

    if ((size = strtoul(argv[2], NULL, 0)) <= 0) {
        fprintf(stderr, "Error: illegal value (%d) specified for [SIZE]");
        fprintf(stderr, " argument. [SIZE] must be greater than zero.\n");
        exit(1);
    }

    /* create the RAM disk image */
    if ((diskBuf = createImage(&size)) == NULL) {
        fprintf(stderr, "ERROR: out of memory, calloc() returned NULL.\n");
        exit(1);
    }

    /* un-register the RAM disk drive */
    if ((result = f_mount(0, NULL)) != FR_OK) {
        fprintf(stderr, "ERROR: un-mounting drive failed: %d\n", result);
        exit(1);
    }

    if (saveImage(diskBuf, size, fileName) < 0) {
        fprintf(stderr, "ERROR: could not save RAM disk image to file %s\n",
                fileName);
        exit(1);
    }

    return 0;
}
