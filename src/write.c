#include "write.h"
#include <unistd.h>

static char	g_buf[4096];
static unsigned short g_idx = 0;

void outflush(t_ctx *ctx) {
	write(*(int *)ctx->write_data, g_buf, g_idx);
	g_idx = 0;
} 

void outc(t_ctx *ctx, char c)
{
	if (g_idx + 1 == 4096)
		outflush(ctx);
	g_buf[g_idx++] = c;
}

void outn(t_ctx *ctx, char *s, size_t n)
{
	while (n--)
		outc(ctx, *s++);
}