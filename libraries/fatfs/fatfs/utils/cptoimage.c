/*
 * ======== cptoimage.c ========
 *
 * copy a file from the local HDD into an existing RAM disk image.
 *
 * Usage:
 *
 *     cptoimage [RAM-disk-filename] [source] [destination]
 *
 *     RAM-disk-filename: name of an existing RAM disk image file (usually
 *                        created with 'mkimage' utility).
 *
 *     source: name of the source file on the local HDD that is to be copied
 *             into the RAM disk image.
 *
 *     destination: name to write the source file to on the RAM disk image.  If
 *                  the file already exists on the RAM disk, it will be
 *                  overwritten.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <ff.h>
#include <fsutils.h>

extern void ramdisk_init(void *, int);

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    unsigned char *diskBuf;
    FRESULT result;
    char *ramImageName;
    unsigned int size = 0;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s ram-file-name [source file]", argv[0]);
        fprintf(stderr, " [destination file]\n");
        exit(1);
    }

    ramImageName = argv[1];

    /* create and mount RAM disk from existing image file */
    if ((diskBuf = loadRamImage(ramImageName, &size)) == NULL) {
        fprintf(stderr, "ERROR: could not load RAM disk image \'%s\'.\n",
                ramImageName);
        exit(1);
    }

    /* copy the local HDD file into the RAM disk */
    if (copyFile(argv[2], argv[3]) < 0) {
        fprintf(stderr, "ERROR: could not copy local file \'%s\'", argv[2]);
        fprintf(stderr, " into RAM disk image file \'%s\'.\n", ramImageName);
        exit(1);
    }


    /* un-register the RAM disk drive */
    if ((result = f_mount(0, NULL)) != FR_OK) {
        fprintf(stderr, "ERROR: un-mounting drive failed: %d\n", result);
        exit(1);
    }

    /* save the updated RAM disk image */
    if (saveImage(diskBuf, size, ramImageName) < 0) {
        fprintf(stderr, "ERROR: could not save RAM disk image to file %s\n",
                ramImageName);
        exit(1);
    }

    return 0;
}
