#include "write_buffer.h"
#include <stdlib.h>
#include <string.h>

static char	g_buf[4096];
static unsigned short g_idx = 0;

void bufferflush(t_ctx *ctx) {
	buffer_wdata *data;

	data = ((buffer_wdata *)ctx->write_data);
	if (data->buffer)
		data->buffer = realloc(data->buffer, sizeof(char) * (data->len + g_idx));
	else
		data->buffer = malloc(sizeof(char) * g_idx);
	data->len = data->len + g_idx;
	memcpy(data->buffer + data->len - g_idx, g_buf, g_idx);
	g_idx = 0;
} 

void bufferc(t_ctx *ctx, char c)
{
	if (g_idx + 1 == 4096)
		bufferflush(ctx);
	g_buf[g_idx++] = c;
}

void buffern(t_ctx *ctx, char *s, size_t n)
{
	if (n > 0)
	{
		((buffer_wdata *)ctx->write_data)->nb += n;
		while (n--)
			bufferc(ctx, *s++);
	}
}

void bufferr(t_ctx *ctx, char s, size_t n)
{
	if (n > 0)
	{
		((buffer_wdata *)ctx->write_data)->nb += n;
		while (n--)
			bufferc(ctx, s);
	}
}