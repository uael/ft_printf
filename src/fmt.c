#include "fmt.h"
#include <string.h>

int	fmt(t_fmt *fmt, t_ctx *ctx)
{
	return (0);
}

int	fmts(t_fmt *fmt, t_ctx *ctx)
{
	TRY(get_arg(fmt->param, PTR, &ctx->va));
	ctx->write(ctx, fmt->param->value.p, strlen(fmt->param->value.p));
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