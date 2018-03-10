/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/fmt/eval.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <string.h>
#include <float.h>
#include <errno.h>

#include "internal.h"

static t_fmtcb	*g_fmts[] = {
	['%' - '%'] = iofmt_fmtpct,
	['s' - '%'] = iofmt_fmts,
	['S' - '%'] = iofmt_fmtsu,
	['p' - '%'] = iofmt_fmtp,
	['X' - '%'] = iofmt_fmtx,
	['x' - '%'] = iofmt_fmtx,
	['O' - '%'] = iofmt_fmto,
	['o' - '%'] = iofmt_fmto,
	['D' - '%'] = iofmt_fmtdi,
	['d' - '%'] = iofmt_fmtdi,
	['i' - '%'] = iofmt_fmtdi,
	['u' - '%'] = iofmt_fmtu,
	['U' - '%'] = iofmt_fmtu,
	['c' - '%'] = iofmt_fmtc,
	['C' - '%'] = iofmt_fmtcu,
	['m' - '%'] = iofmt_fmtm,
};

static ssize_t	evalt(t_stream *s, t_fmt *f, t_varg arg)
{
	t_fmtcb *cb;

	if ((cb = g_fmts[f->type - '%']))
		return (cb(s, f, arg));
	errno = EINVAL;
	return (-1);
}

inline int		iofmt_eval(int t, t_fmt f, t_varg a, t_stream *s)
{
	char		buf[sizeof(uintmax_t) * 3 + 3 + LDBL_MANT_DIG / 4];
	ssize_t		r;

	f.type = t;
	f.pref = "-+   0X0x";
	f.end = buf + sizeof(buf);
	(f.flags & LEFT_ADJ) ? (f.flags &= ~ZERO_PAD) : 0;
	if ((r = evalt(s, &f, a)) || f.done)
		return ((int)r);
	if (f.prec < f.end - f.beg)
		f.prec = (int32_t)(f.end - f.beg);
	if (f.prec > INT_MAX - f.prefl)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	if (f.width < f.prefl + f.prec)
		f.width = (int16_t)(f.prefl + f.prec);
	iofmt_pad(s, ' ', f.width, (size_t)(f.prefl + f.prec), f.flags);
	iofmt_out(s, f.pref, (size_t)f.prefl);
	iofmt_pad(s, '0', f.width, (size_t)(f.prefl + f.prec), f.flags ^ ZERO_PAD);
	iofmt_pad(s, '0', f.prec, f.end - f.beg, 0);
	iofmt_out(s, f.beg, f.end - f.beg);
	iofmt_pad(s, ' ', f.width, (size_t)(f.prefl + f.prec), f.flags ^ LEFT_ADJ);
	return (f.width);
}
