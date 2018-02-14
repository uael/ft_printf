/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "eval.h"
#include "write_out.h"
#include "write_buffer.h"
#include <unistd.h>

ssize_t	ft_printf(char const *fmt, ...)
{
	va_list	ap;
	ssize_t	r;

	va_start(ap, fmt);
	r = ft_vprintf(fmt, ap);
	va_end(ap);
	return (r);
}

ssize_t	ft_vprintf(char const *fmt, va_list ap)
{
	return (ft_vdprintf(STDOUT_FILENO, fmt, ap));
}

ssize_t	ft_dprintf(int fd, char const *fmt, ...)
{
	va_list	ap;
	ssize_t	r;

	va_start(ap, fmt);
	r = ft_vdprintf(fd, fmt, ap);
	va_end(ap);
	return (r);
}

ssize_t	ft_vdprintf(int fd, char const *fmt, va_list ap)
{
	t_ctx ctx;
	out_wdata data;

	data = (out_wdata) {
		.fd = fd,
		.nb = 0,
		.idx = 0
	};
	ctx = (t_ctx) {
		.va = (t_va_slist) {
			.idx = 0,
			.lock = 0
		},
		.idx = 0,
		.write = outn,
		.writer = outr,
		.write_data = &data
	};
	va_copy(ctx.va.ap, ap);
	eval_fmt((char *)fmt, &ctx);
	outflush(&ctx);
	return (data.nb);
}

ssize_t	ft_asprintf(char **out, char const *fmt, ...)
{
	va_list	ap;
	ssize_t	r;

	va_start(ap, fmt);
	r = ft_vasprintf(out, fmt, ap);
	va_end(ap);
	return (r);
}

ssize_t	ft_vasprintf(char **out, char const *fmt, va_list ap)
{
	t_ctx ctx;
	buffer_wdata data;

	data = (buffer_wdata) {
		.buffer = NULL,
		.nb = 0,
		.len = 0,
		.idx = 0
	};
	ctx = (t_ctx) {
		.va = (t_va_slist) {
			.idx = 0,
			.lock = 0
		},
		.idx = 0,
		.write = buffern,
		.writer = bufferr,
		.write_data = &data
	};
	va_copy(ctx.va.ap, ap);
	eval_fmt((char *)fmt, &ctx);
	bufferr(&ctx, 0, 1);
	bufferflush(&ctx);
	*out = data.buffer;
	return (data.nb - 1);
}
