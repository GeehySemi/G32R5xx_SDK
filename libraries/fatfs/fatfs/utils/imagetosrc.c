/*
 * ======== imagetosrc.c ========
 *
 * Converts a RAM disk image into a C array with symbolName.  This C file may
 * then be compiled into an application and loaded as the initial RAM disk for
 * that application.
 *
 * Usage:
 *
 *     imagetosrc [RAM-disk-filename] [output filename] [symbolname]
 *
 *     RAM-disk-filename: name of an existing RAM disk image file (usually
 *                        created with 'mkimage' utility).
 *
 *     output filename: name of the C source file to save the RAM disk image
 *                      data to on the local HDD.
 *
 *     symbol name: name to call the C array, which contains the RAM disk image
 *                  data, within the output file.
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
    char *ramImageName;
    char *filename;
    char *symbolname;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s ram-file-name outputfile symbolname\n",
               argv[0]);
        exit(1);
    }

    ramImageName = argv[1];
    filename     = argv[2];
    symbolname   = argv[3];

    /* create and mount RAM disk from existing image file */
    if ((diskBuf = loadRamImage(ramImageName, &size)) == NULL) {
        fprintf(stderr, "ERROR: could not load RAM disk image \'%s\'.\n",
                ramImageName);
        exit(1);
    }

    if ((result = imageToCfile(diskBuf, size, filename, symbolname)) != 0) {
         printf("ERROR creating RAM disk C file: returned: %d\n", result);
         exit(1);
    }

    /* un-register the RAM disk drive */
    if ((result = f_mount(0, NULL)) != FR_OK) {
        fprintf(stderr, "ERROR: un-mounting drive failed: %d\n", result);
        exit(1);
    }

    return 0;
}
