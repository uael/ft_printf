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
	['s' - '%'] = iofmt_fmts
};

static int		evalt(int t, t_fmt *f, t_varg arg, char *buf)
{
	t_fmtcb *cb;

	if ((cb = g_fmts[t - '%']))
		return (cb(t, f, arg, buf));
	errno = EINVAL;
	return (-1);
}

inline int		iofmt_eval(int t, t_fmt f, t_varg a, t_stream *s)
{
	char		buf[sizeof(uintmax_t) * 3 + 3 + LDBL_MANT_DIG / 4];
	const char	*prefix = "-+   0X0x";
	int			pl;

	f.end = buf + sizeof(buf);
	(f.f & LEFT_ADJ) ? (f.f &= ~ZERO_PAD) : 0;
	if ((pl = evalt(t, &f, a, buf)))
		return (pl);
	if (f.p < f.end - f.beg)
		f.p = (int32_t)(f.end - f.beg);
	if (f.p > INT_MAX - pl)
	{
		errno = EOVERFLOW;
		return (-1);
	}
	if (f.w < pl + f.p)
		f.w = (int16_t)(pl + f.p);
	iofmt_pad(s, ' ', f.w, (size_t)(pl+f.p), f.f);
	iofmt_out(s, prefix, (size_t)pl);
	iofmt_pad(s, '0', f.w, (size_t)(pl+f.p), f.f ^ ZERO_PAD);
	iofmt_pad(s, '0', f.p, f.end - f.beg, 0);
	iofmt_out(s, f.beg, f.end - f.beg);
	iofmt_pad(s, ' ', f.w, (size_t)(pl+f.p), f.f ^ LEFT_ADJ);
	return (f.w);
}
