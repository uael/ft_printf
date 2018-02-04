#include "write.h"
#include <unistd.h>

static char	g_buf[4096];
static unsigned short g_idx = 0;

void outflush(int fd) {
	write(fd, g_buf, g_idx);
	g_idx = 0;
} 

void outc(int fd, char c)
{
	if (g_idx + 1 == 4096)
		outflush(fd);
	g_buf[g_idx++] = c;
}

void outns(int fd, char *s, size_t n)
{
	while (n--)
		outc(fd, *s++);
}

void outs(int fd, char *s)
{
	while (*s)
		outc(fd, *s++);
}