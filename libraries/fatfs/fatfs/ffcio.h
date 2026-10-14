/*
 *  ======== ffcio.h ========
 *
 */

#ifndef FFCIO_
#define FFCIO_

extern int ffcio_close(int dev_fd);
extern fpos_t ffcio_lseek(int dev_fd, fpos_t offset, int origin);
extern int ffcio_open(const char *path, unsigned flags, int llv_fd);
extern int ffcio_read(int dev_fd, char *buf, unsigned count);
extern int ffcio_rename(const char *old_name, const char *new_name);
extern int ffcio_unlink(const char *path);
extern int ffcio_write(int dev_fd, const char *buf, unsigned count);

#endif
