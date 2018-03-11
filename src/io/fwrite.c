/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/fwrite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

#include "internal.h"

static int	towrite(t_stream *f)
{
	f->mode |= f->mode - 1;
	if (f->flags & FT_FNOWR)
	{
		f->flags |= FT_FERRO;
		return (EOF);
	}
	f->rpos = 0;
	f->rend = 0;
	f->wpos = f->buf;
	f->wbase = f->buf;
	f->wend = f->buf + f->buf_size;
	return (0);
}

size_t		fwritex(t_stream *f, uint8_t const *s, size_t l)
{
	size_t i;
	size_t n;

	i = 0;
	if (!f->wend && towrite(f))
		return (0);
	if (l > (size_t)(f->wend - f->wpos))
		return (f->write(f, s, l));
	if (f->lbf >= 0)
	{
		i = l;
		while (i && s[i - 1] != '\n')
			--i;
		if (i)
		{
			n = f->write(f, s, i);
			if (n < i)
				return (n);
			s += i;
			l -= i;
		}
	}
	ft_memcpy(f->wpos, s, l);
	f->wpos += l;
	return (l + i);
}

size_t		ft_fwrite(t_stream *f, void const *src, size_t size, size_t nmemb)
{
	size_t k;
	size_t l;

	l = size * nmemb;
	if (!size)
		nmemb = 0;
	k = fwritex(f, src, l);
	return (k == l ? nmemb : k / size);
}
