/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/fmt/type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

#define S(x) [(x)-'%']
#define OOB(x) ((x)!='%'&&((unsigned)(x)-'A' > 'z'-'A'))

static uint8_t const g_states[]['z'-'%'+1] = {
	{
		S('%') = T_NOARG, S('d') = T_INT, S('i') = T_INT,
		S('o') = T_UINT, S('u') = T_UINT, S('x') = T_UINT, S('X') = T_UINT,
		S('e') = T_DBL, S('f') = T_DBL, S('g') = T_DBL, S('a') = T_DBL,
		S('E') = T_DBL, S('F') = T_DBL, S('G') = T_DBL, S('A') = T_DBL,
		S('c') = T_CHAR, S('C') = T_INT,
		S('s') = T_PTR, S('S') = T_PTR, S('p') = T_UIPTR, S('n') = T_PTR,
		S('m') = T_NOARG,
		S('l') = T_LPRE, S('h') = T_HPRE, S('L') = T_BIGLPRE,
		S('z') = T_ZTPRE, S('j') = T_JPRE, S('t') = T_ZTPRE,
	},
	{
		S('%') = T_NOARG, S('d') = T_LONG, S('i') = T_LONG,
		S('o') = T_ULONG, S('u') = T_ULONG, S('x') = T_ULONG, S('X') = T_ULONG,
		S('e') = T_DBL, S('f') = T_DBL, S('g') = T_DBL, S('a') = T_DBL,
		S('E') = T_DBL, S('F') = T_DBL, S('G') = T_DBL, S('A') = T_DBL,
		S('c') = T_INT, S('s') = T_PTR, S('n') = T_PTR,
		S('l') = T_LLPRE,
	},
	{
		S('%') = T_NOARG, S('d') = T_LLONG, S('i') = T_LLONG,
		S('o') = T_ULLONG, S('u') = T_ULLONG,
		S('x') = T_ULLONG, S('X') = T_ULLONG,
		S('n') = T_PTR,
	},
	{
		S('%') = T_NOARG, S('d') = T_SHORT, S('i') = T_SHORT,
		S('o') = T_USHORT, S('u') = T_USHORT,
		S('x') = T_USHORT, S('X') = T_USHORT,
		S('n') = T_PTR,
		S('h') = T_HHPRE,
	},
	{
		S('%') = T_NOARG, S('d') = T_CHAR, S('i') = T_CHAR,
		S('o') = T_UCHAR, S('u') = T_UCHAR,
		S('x') = T_UCHAR, S('X') = T_UCHAR,
		S('n') = T_PTR,
	},
	{
		S('%') = T_NOARG, S('e') = T_LDBL, S('f') = T_LDBL, S('g') = T_LDBL,
		S('a') = T_LDBL,
		S('E') = T_LDBL, S('F') = T_LDBL, S('G') = T_LDBL, S('A') = T_LDBL,
		S('n') = T_PTR,
	},
	{
		S('%') = T_NOARG, S('d') = T_PDIFF, S('i') = T_PDIFF,
		S('o') = T_SIZET, S('u') = T_SIZET,
		S('x') = T_SIZET, S('X') = T_SIZET,
		S('n') = T_PTR,
	},
	{
		S('%') = T_NOARG, S('d') = T_IMAX, S('i') = T_IMAX,
		S('o') = T_UMAX, S('u') = T_UMAX,
		S('x') = T_UMAX, S('X') = T_UMAX,
		S('n') = T_PTR,
	}
};

static inline void	poparg2(t_varg *arg, int type, va_list ap)
{
	if (type == T_SIZET)
		arg->i = va_arg(ap, size_t);
	else if (type == T_IMAX)
		arg->i = (uintmax_t)va_arg(ap, intmax_t);
	else if (type == T_UMAX)
		arg->i = va_arg(ap, uintmax_t);
	else if (type == T_PDIFF)
		arg->i = (uintmax_t)va_arg(ap, ssize_t);
	else if (type == T_UIPTR)
		arg->i = (uintptr_t)va_arg(ap, void *);
	else if (type == T_DBL)
		arg->f = va_arg(ap, double);
	else if (type == T_LDBL)
		arg->f = va_arg(ap, long double);
}

static inline void	poparg(t_varg *arg, int type, va_list ap)
{
	if (type == T_PTR)
		arg->p = va_arg(ap, void *);
	else if (type == T_INT)
		arg->i = (uintmax_t)va_arg(ap, int);
	else if (type == T_UINT)
		arg->i = va_arg(ap, unsigned int);
	else if (type == T_LONG)
		arg->i = (uintmax_t)va_arg(ap, long);
	else if (type == T_ULONG)
		arg->i = va_arg(ap, unsigned long);
	else if (type == T_ULLONG)
		arg->i = va_arg(ap, unsigned long long);
	else if (type == T_SHORT)
		arg->i = (uintmax_t)(short)va_arg(ap, int);
	else if (type == T_USHORT)
		arg->i = (unsigned short)va_arg(ap, int);
	else if (type == T_CHAR)
		arg->i = (uintmax_t)(signed char)va_arg(ap, int);
	else if (type == T_UCHAR)
		arg->i = (unsigned char)va_arg(ap, int);
	else if (type == T_LLONG)
		arg->i = (uintmax_t)va_arg(ap, long long);
	else
		poparg2(arg, type, ap);
}

inline int			iofmt_poptype(t_varg *arg, int *type, char **s, va_list ap)
{
	uint32_t	st;
	uint32_t	ps;

	st = 0;
	if (OOB(**s))
		return (-1);
	ps = st;
	if (!(st = g_states[st]S(**s)))
		return (-1);
	++*s;
	while (st - 1 < T_STOP)
	{
		if (OOB(**s))
			return (-1);
		ps = st;
		if (!(st = g_states[st]S(**s)))
			return (-1);
		++*s;
	}
	if (st != T_NOARG)
		poparg(arg, st, ap);
	*type = (*s)[-1];
	if (ps && (*type & 15) == 3)
		*type &=~ 32;
	return (st);
}
