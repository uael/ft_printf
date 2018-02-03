/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/23 17:28:28 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/types.h>

ssize_t				ft_printf(char const *fmt, ...);
ssize_t				ft_vprintf(char const *fmt, va_list ap);
ssize_t				ft_dprintf(int fd, char const *fmt, ...);
ssize_t			ft_vdprintf(int fd, char const *fmt, va_list ap);
ssize_t			ft_asnprintf(char **out, char const *fmt, ...);
ssize_t			ft_vasnprintf(char **out, char const *fmt, va_list ap);

typedef struct	s_fmt
{
	size_t			idx;
	size_t			param;
	uint8_t			flags;
	int32_t			width;
	size_t			widthparam;
	int32_t			precision;
	size_t			precisionparam;
	uint8_t			length;
	char 			*begin;
	char 			*end;
	struct s_fmt	*next;
}				t_fmt;

#define TIDX(i) ((i) - '%')

typedef void	(t_pf)(t_fmt *fmt, va_list ap);

void			fmt(t_fmt *fmt, va_list ap);
void			fmts(t_fmt *fmt, va_list ap);
void			fmtsu(t_fmt *fmt, va_list ap);
void			fmtp(t_fmt *fmt, va_list ap);
void			fmtd(t_fmt *fmt, va_list ap);
void			fmtdu(t_fmt *fmt, va_list ap);
void			fmti(t_fmt *fmt, va_list ap);
void			fmto(t_fmt *fmt, va_list ap);
void			fmtou(t_fmt *fmt, va_list ap);
void			fmtu(t_fmt *fmt, va_list ap);
void			fmtuu(t_fmt *fmt, va_list ap);
void			fmtx(t_fmt *fmt, va_list ap);
void			fmtxu(t_fmt *fmt, va_list ap);
void			fmtc(t_fmt *fmt, va_list ap);
void			fmtcu(t_fmt *fmt, va_list ap);

static t_pf		*g_pf[] =
{
	[TIDX('%')] = fmt,
	[TIDX('s')] = fmts,
	[TIDX('S')] = fmtsu,
	[TIDX('p')] = fmtp,
	[TIDX('d')] = fmtd,
	[TIDX('D')] = fmtdu,
	[TIDX('i')] = fmti,
	[TIDX('o')] = fmto,
	[TIDX('O')] = fmtou,
	[TIDX('u')] = fmtu,
	[TIDX('U')] = fmtuu,
	[TIDX('x')] = fmtx,
	[TIDX('X')] = fmtxu,
	[TIDX('c')] = fmtc,
	[TIDX('C')] = fmtcu,
};

enum			e_pfflags
{
	PF_HASH = 1 << 1,
	PF_ZERO = 1 << 2,
	PF_MINUS = 1 << 3,
	PF_PLUS = 1 << 4,
	PF_SPACE = 1 << 5
};

enum			e_pfelens
{
	PF_H = 1 << 1,
	PF_HH = 1 << 2,
	PF_L = 1 << 3,
	PF_LL = 1 << 4,
	PF_J = 1 << 5,
	PF_Z = 1 << 6
};

#define FIDX(i) ((i) - ' ')
#define LIDX(i) ((i) - 'h')

static	enum e_pfflags	g_flags[] =
{
	[FIDX('#')] = PF_HASH,
	[FIDX('0')] = PF_ZERO,
	[FIDX('-')] = PF_MINUS,
	[FIDX('+')] = PF_PLUS,
	[FIDX(' ')] = PF_SPACE,
};

static	enum e_pfflags	g_elens[] =
{
	[LIDX('h')] = PF_H,
	[LIDX('l')] = PF_L,
	[LIDX('j')] = PF_J,
	[LIDX('z')] = PF_Z,
};

typedef union			u_pfarg
{
	uintmax_t			i;
	long double			f;
	void				*p;
}						t_pfarg;

#endif
