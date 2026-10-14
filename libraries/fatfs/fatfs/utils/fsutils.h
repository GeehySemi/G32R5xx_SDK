/*
 *  ======== fsutils.h ========
 *
 */

#ifndef FSUTILS_
#define FFUTILS_

#include <ff.h>

extern unsigned char *createImage(unsigned int *size);
extern FRESULT catTextFile(char *filename);
extern int copyFile(char *src, char *dst);
extern int imageToCfile(unsigned char *image, unsigned int imagesize,
        char *filename, char *symbolname);
extern unsigned char *loadRamImage(char *name, unsigned int *len);
extern int saveImage(unsigned char *data, unsigned int len, char *filename);
extern FRESULT scanFiles (char* path);

#endif /* FSUTILS_ */
