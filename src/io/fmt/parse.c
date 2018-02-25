/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/fmt/parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <limits.h>
#include <string.h>

#include "../fmt.h"

static inline int	atoio(char **s)
{
	int i;

	i = 0;
	while (isdigit(**s))
	{
		if ((size_t)i > INT_MAX / 10U || (**s - '0') > INT_MAX - 10 * i)
			i = -1;
		else
			i = 10 * i + (**s - '0');
		++*s;
	}
	return (i);
}

inline int			iofmt_parse(t_fmt *f, char **sp)
{
	bzero(f, sizeof(t_fmt));
	while ((**sp - ' ') < 32 && (FLAGMASK & (1U << (**sp - ' '))))
		f->f |= 1U << (*(*sp)++ - ' ');
	if ((f->w = atoio(sp) < 0))
		return (-1);
	if (**sp == '.')
	{
		++*sp;
		f->p = atoio(sp);
	}
	else
		f->p = -1;
	return (0);
}
