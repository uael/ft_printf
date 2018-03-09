/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fmt.h"

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

inline size_t		iofmt_out(t_stream *f, const char *s, size_t l)
{
	if (!(f->flags & FT_FERRO))
		return (fwritex(f, (void *)s, l));
	return (l);
}

inline void			iofmt_pad(t_stream *f, char c, int w, size_t l, int fl)
{
	char pad[256];

	if ((fl & (LEFT_ADJ | ZERO_PAD)) || l >= (size_t)w)
		return ;
	l = w - l;
	memset(pad, c, l > sizeof pad ? sizeof pad : l);
	while (l >= sizeof pad)
	{
		iofmt_out(f, pad, sizeof pad);
		l -= sizeof pad;
	}
	iofmt_out(f, pad, l);
}

static inline int	doerr(int err)
{
	errno = err;
	return (-1);
}

static inline int	printarg(t_stream *f, char **pct, va_list ap)
{
	int		type;
	int		len;
	t_fmt	fm;
	t_varg	arg;

	if (iofmt_parse(&fm, pct, ap))
		return (doerr(EOVERFLOW));
	if (iofmt_poptype(&arg, &type, pct, ap) < 0)
	{
		type = 'c';
		arg.i = (uintmax_t)*(*pct)++;
	}
	if ((len = iofmt_eval(type, fm, arg, f)) < 0)
		return (len == -2 ? -1 : 0);
	return (len);
}

inline int			ft_vfprintf(t_stream *f, char const *fmt, va_list ap)
{
	int		len;
	size_t	ret;
	char	*pct;

	ret = 0;
	while ((pct = strchr(fmt, '%')))
	{
		if ((ret += iofmt_out(f, fmt, pct++ - fmt)) > INT_MAX)
			return (doerr(EOVERFLOW));
		if (!*pct)
		{
			fmt = pct;
			break ;
		}
		if ((len = printarg(f, &pct, ap)) < 0 || len + ret > INT_MAX)
			return (doerr(EOVERFLOW));
		ret += len;
		fmt = pct;
	}
	len = ((ret += iofmt_out(f, fmt, strlen(fmt))) > INT_MAX
		? doerr(EOVERFLOW) : (int)ret);
	ft_fflush(f);
	return (len);
}
