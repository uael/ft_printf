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

#include <errno.h>
#include <libft.h>
#include <limits.h>
#include <stdlib.h>

#include "internal.h"

ssize_t			iofmt_fmts(t_stream *s, t_fmt *f, t_varg arg)
{
	(void)s;
	f->beg = arg.p ? arg.p : "(null)";
	f->end = f->beg + ft_strnlen(f->beg,
		(size_t)(f->prec < 0 ? INT_MAX : f->prec));
	if (f->prec < 0 && *f->end)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	f->prec = (int32_t)(f->end - f->beg);
	return (0);
}

static ssize_t	suout(t_stream *s, t_fmt *f, t_varg arg)
{
	size_t	i;
	int		l;
	wchar_t	*ws;
	char	mb[MB_CUR_MAX];

	iofmt_pad(s, ' ', f->width, (size_t)f->prec, f->flags);
	iofmt_pad(s, '0', f->width, (size_t)f->prec, f->flags ^ ZERO_PAD);
	iofmt_pad(s, '0', f->prec, f->end - f->beg, 0);
	ws = arg.p;
	i = 0;
	while (i < (size_t)f->prec && *ws &&
		(i + (l = ft_wctomb(mb, *ws++))) <= (size_t)f->prec)
	{
		iofmt_out(s, mb, (size_t)l);
		i += l;
	}
	iofmt_pad(s, ' ', f->width, (size_t)f->prec, f->flags ^ LEFT_ADJ);
	return (f->width > f->prec ? f->width : f->prec);
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
	while (i < (size_t)f->prec && *ws &&
		(l = ft_wctomb(mb, *ws++)) >= 0 && (size_t)l <= (size_t)(f->prec - i))
		i += l;
	if (l < 0)
		return (-2);
	if (i > INT_MAX)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	f->prec = (int)i;
	return (suout(s, f, arg));
}

ssize_t			iofmt_fmtc(t_stream *s, t_fmt *f, t_varg arg)
{
	(void)s;
	f->prec = 1;
	f->beg = f->end - f->prec;
	*f->beg = (char)arg.i;
	return (0);
}

ssize_t			iofmt_fmtcu(t_stream *s, t_fmt *f, t_varg arg)
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
