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

#include "internal.h"

ssize_t			iofmt_fmtm(t_stream *s, t_fmt *f, t_varg arg)
{
	(void)s;
	(void)arg;
	f->beg = ft_strerr(errno);
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
