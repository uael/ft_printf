#ifndef FT_PRINTF_FMT_H
# define FT_PRINTF_FMT_H

# include "eval.h"

typedef int	(t_pf)(t_fmt *fmt, t_ctx *ctx);

int			fmt(t_fmt *fmt, t_ctx *ctx);
int			fmts(t_fmt *fmt, t_ctx *ctx);
int			fmtsu(t_fmt *fmt, t_ctx *ctx);
int			fmtp(t_fmt *fmt, t_ctx *ctx);
int			fmtd(t_fmt *fmt, t_ctx *ctx);
int			fmtdu(t_fmt *fmt, t_ctx *ctx);
int			fmti(t_fmt *fmt, t_ctx *ctx);
int			fmto(t_fmt *fmt, t_ctx *ctx);
int			fmtou(t_fmt *fmt, t_ctx *ctx);
int			fmtu(t_fmt *fmt, t_ctx *ctx);
int			fmtuu(t_fmt *fmt, t_ctx *ctx);
int			fmtx(t_fmt *fmt, t_ctx *ctx);
int			fmtxu(t_fmt *fmt, t_ctx *ctx);
int			fmtc(t_fmt *fmt, t_ctx *ctx);
int			fmtcu(t_fmt *fmt, t_ctx *ctx);

#define TIDX(i) ((i) - '%')

static t_pf		*g_pf[] =
{
	[TIDX('%')] = fmt,
	[TIDX('s')] = fmts,
	[TIDX('S')] = fmtsu,
	[TIDX('p')] = fmtp,
	[TIDX('d')] = fmtd,
	[TIDX('D')] = fmtdu,
	[TIDX('i')] = fmti,
	[TIDX('o')] = fmto,
	[TIDX('O')] = fmtou,
	[TIDX('u')] = fmtu,
	[TIDX('U')] = fmtuu,
	[TIDX('x')] = fmtx,
	[TIDX('X')] = fmtxu,
	[TIDX('c')] = fmtc,
	[TIDX('C')] = fmtcu,
};

# define TRY(expr) if(expr == -1) return (-1)

#endif