/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/fmt/fmt_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <string.h>
#include <errno.h>
#include <wchar.h>
#include <stdlib.h>
#include <sys/param.h>

#include "internal.h"

static char *g_xdigits = "0123456789ABCDEF";

ssize_t			iofmt_fmtpct(t_stream *s, t_fmt *f, t_varg arg)
{
	(void)s;
	(void)arg;
	if (f->xp && !f->prec)
		f->prec = -1;
	f->beg = "%";
	f->end = f->beg + strnlen(f->beg, (size_t)(f->prec < 0 ? INT_MAX : f->prec));
	if (f->prec < 0 && *f->end)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	f->prec = (int32_t)(f->end - f->beg);
	return (0);
}

ssize_t			iofmt_fmtm(t_stream *s, t_fmt *f, t_varg arg)
{
	(void)s;
	(void)arg;
	f->beg = strerror(errno);
	f->end = f->beg + strnlen(f->beg, (size_t)(f->prec < 0 ? INT_MAX : f->prec));
	if (f->prec < 0 && *f->end)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	f->prec = (int32_t)(f->end - f->beg);
	return (0);
}

ssize_t			iofmt_fmts(t_stream *s, t_fmt *f, t_varg arg)
{
	(void)s;
	f->beg = arg.p ? arg.p : "(null)";
	f->end = f->beg + strnlen(f->beg, (size_t)(f->prec < 0 ? INT_MAX : f->prec));
	if (f->prec < 0 && *f->end)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	f->prec = (int32_t)(f->end - f->beg);
	return (0);
}

#define IS_CODEUNIT(c) ((unsigned)(c)-0xdf80 < 0x80)

int	ft_wctomb(char *s, wchar_t wc)
{
	if (!s)
		return (1);
	if ((unsigned)wc < 0x80)
	{
		*s = (char)wc;
		return (1);
	}
	else if (MB_CUR_MAX == 1)
	{
		if (!IS_CODEUNIT(wc))
		{
			errno = EILSEQ;
			return (-1);
		}
		*s = (char)wc;
		return (1);
	}
	else if ((unsigned)wc < 0x800)
	{
		*s++ = (char)(0xc0 | (wc >> 6));
		*s = (char)(0x80 | (wc & 0x3f));
		return (2);
	}
	else if ((unsigned)wc < 0xd800 || (unsigned)wc - 0xe000 < 0x2000)
	{
		*s++ = (char)(0xe0 | (wc >> 12));
		*s++ = (char)(0x80 | ((wc >> 6) & 0x3f));
		*s = (char)(0x80 | (wc & 0x3f));
		return (3);
	}
	else if ((unsigned)wc - 0x10000 < 0x100000)
	{
		*s++ = (char)(0xf0 | (wc >> 18));
		*s++ = (char)(0x80 | ((wc >> 12) & 0x3f));
		*s++ = (char)(0x80 | ((wc >> 6) & 0x3f));
		*s = (char)(0x80 | (wc & 0x3f));
		return (4);
	}
	errno = EILSEQ;
	return (-1);
}

ssize_t			iofmt_fmtsu(t_stream *s, t_fmt *f, t_varg arg)
{
	size_t	i;
	int		l;
	wchar_t	*ws;
	char	mb[MB_CUR_MAX];

	if (!(ws = arg.p))
		return (iofmt_fmts(s, f, arg));
	f->done = 1;
	i = 0;
	l = 0;
	while (i < (size_t)f->prec && *ws && (l = ft_wctomb(mb, *ws++)) >= 0 && (size_t)l <= (size_t)(f->prec - i))
		i += l;
	if (l < 0)
		return (-2);
	if (i > INT_MAX)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	f->prec = (int)i;
	iofmt_pad(s, ' ', f->width, (size_t)f->prec, f->flags);
	iofmt_pad(s, '0', f->width, (size_t)f->prec, f->flags ^ ZERO_PAD);
	iofmt_pad(s, '0', f->prec, f->end - f->beg, 0);
	ws = arg.p;
	i = 0;
	while (i < (size_t)f->prec && *ws && i + (l = ft_wctomb(mb, *ws++)) <= (size_t)f->prec)
	{
		iofmt_out(s, mb, (size_t)l);
		i += l;
	}
	iofmt_pad(s, ' ', f->width, (size_t)f->prec, f->flags ^ LEFT_ADJ);
	return (f->width > f->prec ? f->width : f->prec);
}

static ssize_t	fmtxp(t_stream *s, t_fmt *f, t_varg arg)
{
	(void)s;
	if (f->xp && f->prec < 0)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	if (f->xp)
		f->flags &= ~ZERO_PAD;
	if (!arg.i && !f->prec)
	{
		f->beg = f->end;
		return (0);
	}
	if (f->end - f->beg + !arg.i)
		f->prec = MAX(f->prec, (int32_t)(f->end - f->beg + !arg.i));
	return (0);
}

ssize_t			iofmt_fmtp(t_stream *s, t_fmt *f, t_varg arg)
{
	uintmax_t	x;
	char		*z;

	x = arg.i;
	z = f->end;
	while (x)
	{
		*--z = (char)(g_xdigits[x & 15] | (f->type & 32));
		x >>= 4;
	}
	f->beg = z;
	f->pref += ('x' >> 4);
	f->prefl = 2;
	return (fmtxp(s, f, arg));
}

ssize_t			iofmt_fmtx(t_stream *s, t_fmt *f, t_varg arg)
{
	uintmax_t	x;
	char		*z;

	(void)s;
	x = arg.i;
	z = f->end;
	while (x)
	{
		*--z = (char)(g_xdigits[x & 15] | (f->type & 32));
		x >>= 4;
	}
	f->beg = z;
	if ((f->flags & ALT_FORM) && arg.i)
	{
		f->pref += (f->type >> 4);
		f->prefl = 2;
	}
	return (fmtxp(s, f, arg));
}

ssize_t			iofmt_fmto(t_stream *s, t_fmt *f, t_varg arg)
{
	uintmax_t	x;
	char		*z;

	(void)s;
	x = arg.i;
	z = f->end;
	while (x)
	{
		*--z = (char)('0' + (x & 7));
		x >>= 3;
	}
	f->beg = z;
	if ((f->flags & ALT_FORM) && f->prec < f->end - f->beg + 1)
		f->prec = (int32_t)(f->end - f->beg + 1);
	return (fmtxp(s, f, arg));
}

ssize_t			iofmt_fmtdi(t_stream *s, t_fmt *f, t_varg arg)
{
	(void)s;
	f->prefl = 1;
	if (arg.i > INTMAX_MAX)
		arg.i = (uintmax_t)-arg.i;
	else if ((f->flags & MARK_POS))
		++f->pref;
	else if ((f->flags & PAD_POS))
		f->pref += 2;
	else
		f->prefl = 0;
	return (iofmt_fmtu(s, f, arg));
}

ssize_t	iofmt_fmtu(t_stream *s, t_fmt *f, t_varg arg)
{
	uintmax_t		x;
	char			*z;
	unsigned long	y;

	(void)s;
	x = arg.i;
	z = f->end;
	while (x > ULONG_MAX)
	{
		*--z = (char)('0' + x % 10);
		x /= 10;
	}
	y = x;
	while (y)
	{
		*--z = (char)('0' + y % 10);
		y /= 10;
	}
	f->beg = z;
	return (fmtxp(s, f, arg));
}

ssize_t	iofmt_fmtc(t_stream *s, t_fmt *f, t_varg arg)
{
	(void)s;
	f->prec = 1;
	f->beg = f->end - f->prec;
	*f->beg = (char)arg.i;
	return (0);
}

ssize_t	iofmt_fmtcu(t_stream *s, t_fmt *f, t_varg arg)
{
	(void)s;
	f->wc[0] = (wchar_t)arg.i;
	f->wc[1] = 0;
	arg.p = f->wc;
	if (!*((wchar_t	*)arg.p))
		return (1);
	f->prec = -1;
	return (iofmt_fmtsu(s, f, arg));
}
