/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>

#include "internal.h"

ssize_t	writeloop(int fd, uint8_t const *buf, size_t len)
{
	size_t	outc;
	ssize_t	out;

	outc = 0;
	while (outc < len)
	{
		if ((out = write(fd, buf + outc, len - outc)) > 0)
			outc += (size_t)out;
		else if (out && (errno != EAGAIN && errno != EINTR))
			return (-1);
	}
	return (ssize_t)outc;
}

size_t	stdiowrite(t_stream *f, uint8_t const *s, size_t len)
{
	size_t	outc;
	ssize_t	out;

	if ((outc = f->wpos - f->wbase))
	{
		if ((out = writeloop(f->fd, f->wbase, outc)) < 0)
		{
			f->wpos = NULL;
			f->wbase = NULL;
			f->wend = NULL;
			f->flags |= FT_FERRO;
			return (0);
		}
		outc = (size_t)out;
	}
	out = 0;
	if (len && ((out = writeloop(f->fd, s, len)) < 0))
	{
		f->wpos = NULL;
		f->wbase = NULL;
		f->wend = NULL;
		f->flags |= FT_FERRO;
		return (0);
	}
	return (outc + out);
}

int		stdioclose(t_stream *f)
{
	return (close(f->fd));
}
