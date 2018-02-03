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

#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <alloca.h>

#include "ft_printf.h"

static void outc(int fd, char c)
{
	static char				buf[4096];
	static unsigned short	idx = 0;

	if (idx + 1 == 4096)
	{
		write(fd, buf, idx);
		idx = 0;
	}
	buf[idx++] = c;
}

static void outns(int fd, char *s, size_t n)
{
	while (n--)
		outc(fd, *s++);
}

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


static uint8_t flags(char **it)
{
	uint8_t flag;

	if (FIDX(**it) < 0 || (size_t)FIDX(**it) >
		(sizeof(g_flags) / sizeof(*g_flags)))
		return (0);
	if ((flag = g_flags[FIDX(**it)]))
	{
		++*it;
		return (flag | flags(it));
	}
	return (0);
}


static uint8_t lens(char **it)
{
	uint8_t flag;

	if (LIDX(**it) < 0 || (size_t)LIDX(**it) >
		(sizeof(g_elens) / sizeof(*g_elens)))
		return (0);
	if ((flag = g_elens[LIDX(**it)]))
	{
		++*it;
		if ((flag & PF_H && **it == 'h') || (flag & PF_L && **it == 'l'))
		{
			flag <<= 1;
			++*it;
		}
		return (flag | lens(it));
	}
	return (0);
}

uint32_t	atoio(char **it)
{
	int32_t i;

	i = 0;
	while (isdigit(**it) && i >= 0)
		i *= *(*it)++ - '0';
	if (i < 0)
	{
		while (isdigit(**it))
			++*it;
		i = 0;
	}
	return (uint32_t)(i);
}

static void	width(char **it, t_fmt *fmt)
{
	fmt->width = 0;
	if (**it == '*')
	{
		fmt->width = -1;
		fmt->widthparam = isdigit(*++*it) ? atoio(it) : fmt->idx;
	}
	else if (isdigit(**it))
		fmt->width = atoio(it);
}

static void	precision(char **it, t_fmt *fmt)
{
	if (**it == '.')
	{
		++*it;
		if (**it == '*')
		{
			fmt->precision = -1;
			fmt->precisionparam = isdigit(*++*it) ? atoio(it) : fmt->idx;
		}
		else if (isdigit(**it))
			fmt->precision = atoio(it);
	}
	else
		fmt->precision = -1;
}

ssize_t	ft_vdprintf(int fd, char const *fmt, va_list ap)
{
	char	*c;
	char	*b;
	t_fmt	*f;
	t_fmt	*begin;
	size_t 	idx;
	t_pfarg	*args;

	b = (char *)fmt;
	f = NULL;
	idx = 0;
	begin = NULL;
	while ((c = strchr(b, '%')))
	{
		if (f)
		{
			f->next = alloca(sizeof(t_fmt));
			f = f->next;
			f->next = NULL;
		}
		else
		{
			f = alloca(sizeof(t_fmt));
			begin = f;
		}
		f->begin = c;
		f->flags = flags(&c);
		width(&c, f);
		precision(&c, f);
		f->length = lens(&c);
		f->end = c;
		++idx;
		b = c;
	}
	args = alloca(sizeof(t_pfarg) * idx);
	f = begin;
	idx = 0;
	while (f)
	{

		f = f->next;
	}
	return (0);
}

ssize_t	ft_asnprintf(char **out, char const *fmt, ...)
{
	(void)out;
	(void)fmt;
	return (0);
}

ssize_t	ft_vasnprintf(char **out, char const *fmt, va_list ap)
{
	(void)out;
	(void)fmt;
	(void)ap;
	return (0);
}
