/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/fmt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_FMT_H
# define IO_FMT_H

# include "internal.h"

#define ALT_FORM   (1U<<('#'-' '))
#define ZERO_PAD   (1U<<('0'-' '))
#define LEFT_ADJ   (1U<<('-'-' '))
#define PAD_POS    (1U<<(' '-' '))
#define MARK_POS   (1U<<('+'-' '))
#define GROUPED    (1U<<('\''-' '))

#define FLAGMASK (ALT_FORM|ZERO_PAD|LEFT_ADJ|PAD_POS|MARK_POS|GROUPED)

typedef union	u_varg
{
	uintmax_t	u;
	intmax_t	i;
	long double	f;
	void		*p;
}				t_varg;

typedef struct	s_fmt
{
	uint8_t		f;
	int16_t		w;
	int32_t		p;
	char		*beg;
	char		*end;
}				t_fmt;

extern int		iofmt_parse(t_fmt *f, char **sp);
extern int		iofmt_poptype(t_varg *arg, int *type, char **s, va_list ap);
extern size_t	iofmt_out(t_stream *f, const char *s, size_t l);
extern void		iofmt_pad(t_stream *f, char c, int w, size_t l, int fl);
extern int		iofmt_eval(int t, t_fmt f, t_varg a, t_stream *s);

#endif
