/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vdprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/uio.h>

#include "ft_printf.h"

static size_t	dwrite(t_stream *f, uint8_t const *buf, size_t len)
{
	(void)f;
	(void)buf;
	(void)len;
	return (0);
}

int				ft_vdprintf(int fd, const char *fmt, va_list ap)
{
	t_stream f;

	f = (t_stream){
		.fd = fd,
		.lbf = EOF,
		.write = dwrite,
		.buf = (void *)fmt,
		.buf_size = 0,
		.lock = -1
	};
	return (ft_vfprintf(&f, fmt, ap));
}
