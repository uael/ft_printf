#ifndef FT_PRINTF_WRITE_H
# define FT_PRINTF_WRITE_H

# include <sys/types.h>

void outflush(int fd);
void outc(int fd, char c);
void outns(int fd, char *s, size_t n);
void outs(int fd, char *s);

#endif