#include "write_out.h"
#include <unistd.h>

void outflush(t_ctx *ctx)
{
	out_wdata *data;

	data = (out_wdata *)ctx->write_data;
	write(data->fd, data->buf, data->idx);
	data->idx = 0;
} 

void outc(t_ctx *ctx, char c)
{
	out_wdata *data;

	data = (out_wdata *)ctx->write_data;
	if (data->idx + 1 == 4096)
		outflush(ctx);
	data->buf[data->idx++] = c;
}

void outn(t_ctx *ctx, char *s, size_t n)
{
	if (n > 0)
	{
		((out_wdata *)ctx->write_data)->nb += n;
		while (n--)
			outc(ctx, *s++);
	}
}

void outr(t_ctx *ctx, char s, size_t n)
{
	if (n > 0)
	{
		((out_wdata *)ctx->write_data)->nb += n;
		while (n--)
			outc(ctx, s);
	}
}