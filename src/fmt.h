#ifndef FT_PRINTF_FMT_H
# define FT_PRINTF_FMT_H

# include "eval.h"

typedef int	(t_pf)(t_fmt *fmt, t_va_slist *ap);

int			fmt(t_fmt *fmt, t_va_slist *ap);
int			fmts(t_fmt *fmt, t_va_slist *ap);
int			fmtsu(t_fmt *fmt, t_va_slist *ap);
int			fmtp(t_fmt *fmt, t_va_slist *ap);
int			fmtd(t_fmt *fmt, t_va_slist *ap);
int			fmtdu(t_fmt *fmt, t_va_slist *ap);
int			fmti(t_fmt *fmt, t_va_slist *ap);
int			fmto(t_fmt *fmt, t_va_slist *ap);
int			fmtou(t_fmt *fmt, t_va_slist *ap);
int			fmtu(t_fmt *fmt, t_va_slist *ap);
int			fmtuu(t_fmt *fmt, t_va_slist *ap);
int			fmtx(t_fmt *fmt, t_va_slist *ap);
int			fmtxu(t_fmt *fmt, t_va_slist *ap);
int			fmtc(t_fmt *fmt, t_va_slist *ap);
int			fmtcu(t_fmt *fmt, t_va_slist *ap);

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