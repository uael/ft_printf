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
};

static ssize_t	evalt(t_stream *s, t_fmt *f, t_varg arg, char *buf)
{
	t_fmtcb *cb;

	if ((cb = g_fmts[f->t - '%']))
		return (cb(s, f, arg, buf));
	errno = EINVAL;
	return (-1);
}

inline int		iofmt_eval(int t, t_fmt f, t_varg a, t_stream *s)
{
	char		buf[sizeof(uintmax_t) * 3 + 3 + LDBL_MANT_DIG / 4];
	ssize_t		r;

	f.t = t;
	f.prefix = "-+   0X0x";
	f.end = buf + sizeof(buf);
	(f.f & LEFT_ADJ) ? (f.f &= ~ZERO_PAD) : 0;
	if ((r = evalt(s, &f, a, buf)))
		return ((int)r);
	if (f.p < f.end - f.beg)
		f.p = (int32_t)(f.end - f.beg);
	if (f.p > INT_MAX - f.pl)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	if (f.w < f.pl + f.p)
		f.w = (int16_t)(f.pl + f.p);
	iofmt_pad(s, ' ', f.w, (size_t)(f.pl + f.p), f.f);
	iofmt_out(s, f.prefix, (size_t)f.pl);
	iofmt_pad(s, '0', f.w, (size_t)(f.pl + f.p), f.f ^ ZERO_PAD);
	iofmt_pad(s, '0', f.p, f.end - f.beg, 0);
	iofmt_out(s, f.beg, f.end - f.beg);
	iofmt_pad(s, ' ', f.w, (size_t)(f.pl + f.p), f.f ^ LEFT_ADJ);
	return (f.w);
}
