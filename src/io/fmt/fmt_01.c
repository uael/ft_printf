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

#include "internal.h"

static char *g_xdigits = "0123456789ABCDEF";

ssize_t			iofmt_fmtpct(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	(void)s;
	(void)buf;
	(void)arg;
	f->beg = "%";
	f->end = f->beg + strnlen(f->beg, (size_t)(f->p < 0 ? INT_MAX : f->p));
	if (f->p < 0 && *f->end)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	f->p = (int32_t)(f->end - f->beg);
	f->f &= ~ZERO_PAD;
	return (0);
}

ssize_t			iofmt_fmts(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	(void)s;
	(void)buf;
	f->beg = arg.p ? arg.p : "(null)";
	f->end = f->beg + strnlen(f->beg, (size_t)(f->p < 0 ? INT_MAX : f->p));
	if (f->p < 0 && *f->end)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	f->p = (int32_t)(f->end - f->beg);
	f->f &= ~ZERO_PAD;
	return (0);
}

ssize_t			iofmt_fmtsu(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	int		i;
	int		l;
	wchar_t	*ws;
	char	mb[4];

	(void)buf;
	ws = arg.p;
	i = 0;
	l = 0;
	while (i < f->p && *ws && (l = wctomb(mb, *ws++)) >= 0 && l <= f->p - i)
		i += l;
	if (l < 0)
		return (-1);
	if (i > INT_MAX)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	f->p = i;
	iofmt_pad(s, ' ', f->w, (size_t)f->p, f->f);
	ws = arg.p;
	i = 0;
	while ((unsigned)i < 0U + f->p && *ws && i + (l = wctomb(mb, *ws++)) <= f->p)
	{
		iofmt_out(s, mb, (size_t)l);
		i += l;
	}
	iofmt_pad(s, ' ', f->w, (size_t)f->p, f->f ^ LEFT_ADJ);
	return (f->w > f->p ? f->w : f->p);
}

ssize_t			iofmt_fmtp(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	(void)buf;
	if (2 * sizeof(void*) > (size_t)f->p)
		f->p = sizeof(void *);
	f->t = 'x';
	f->f |= ALT_FORM;
	return (iofmt_fmtx(s, f, arg, buf));
}

static ssize_t	fmtxp(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	(void)s;
	(void)buf;
	if (f->xp && f->p<0)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	if (f->xp)
		f->f &= ~ZERO_PAD;
	if (!arg.i && !f->p)
	{
		f->beg = f->end;
		return (0);
	}
	if (f->end - f->beg + !arg.i)
		f->p = (int32_t)(f->end - f->beg + !arg.i);
	return (0);
}

ssize_t			iofmt_fmtx(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	uintmax_t	x;
	char		*z;

	(void)s;
	(void)buf;
	x = arg.i;
	z = f->end;
	while (x)
	{
		*--z = (char)(g_xdigits[x & 15] | (f->t & 32));
		x >>= 4;
	}
	f->beg = z;
	if ((f->f & ALT_FORM))
	{
		f->prefix += (f->t >> 4);
		f->pl = 2;
	}
	return (fmtxp(s, f, arg, buf));
}

ssize_t			iofmt_fmto(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	uintmax_t	x;
	char		*z;

	(void)s;
	(void)buf;
	x = arg.i;
	z = f->end;
	while (x)
	{
		*--z = (char)('0' + (x & 7));
		x >>= 3;
	}
	f->beg = z;
	if ((f->f & ALT_FORM) && f->p < f->end - f->beg + 1)
		f->p = (int32_t)(f->end - f->beg + 1);
	return (fmtxp(s, f, arg, buf));
}

ssize_t			iofmt_fmtdi(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	(void)s;
	(void)buf;
	f->pl = 1;
	if (arg.i > INTMAX_MAX)
		arg.i = (uintmax_t)-arg.i;
	else if ((f->f & MARK_POS))
		++f->prefix;
	else if ((f->f & PAD_POS))
		f->prefix += 2;
	else
		f->pl = 0;
	return (iofmt_fmtu(s, f, arg, buf));
}

ssize_t	iofmt_fmtu(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	uintmax_t		x;
	char			*z;
	unsigned long	y;

	(void)s;
	(void)buf;
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
	return (fmtxp(s, f, arg, buf));
}

ssize_t	iofmt_fmtc(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	(void)s;
	(void)buf;
	f->p = 1;
	f->beg = f->end - f->p;
	*f->beg = (char)arg.i;
	f->f &= ~ZERO_PAD;
	return (0);
}

ssize_t	iofmt_fmtcu(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	(void)s;
	(void)buf;
	f->wc[0] = (wchar_t)arg.i;
	f->wc[1] = 0;
	arg.p = f->wc;
	f->p = -1;
	return (iofmt_fmtsu(s, f, arg, buf));
}
