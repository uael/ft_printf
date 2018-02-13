#include "fmt.h"
#include "parse.h"
#include <string.h>

int	fmt(t_fmt *fmt, t_ctx *ctx)
{
	ctx->writer(ctx, '%', 1);
	return (0);
}

int	fmts(t_fmt *fmt, t_ctx *ctx)
{
	size_t len;

	TRY(get_arg(fmt->param, PTR, &ctx->va));
	len = fmt->param->value.p ? strlen(fmt->param->value.p) : 6;
	if (!(fmt->flags & PF_MINUS) && len < fmt->width)
		ctx->writer(ctx, ' ', fmt->width - len);
	if (fmt->param->value.p)
		ctx->write(ctx, fmt->param->value.p, len);
	else
		ctx->write(ctx, "(null)", 6);
	if (fmt->flags & PF_MINUS && len < fmt->width)
		ctx->writer(ctx, ' ', fmt->width - len);
	return (0);
}

int	fmtsu(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmtp(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmtd(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmtdu(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmti(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmto(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmtou(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmtu(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmtuu(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmtx(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmtxu(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmtc(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmtcu(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}