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
#include <float.h>
#include <errno.h>

#include "internal.h"

int		iofmt_fmts(int t, t_fmt *f, t_varg arg, char *buf)
{
	(void)t;
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
