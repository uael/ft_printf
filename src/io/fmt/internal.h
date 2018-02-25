/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/fmt/internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_FMT_INTERNAL_H
# define IO_FMT_INTERNAL_H

# include "../fmt.h"

enum {
	T_BARE, T_LPRE, T_LLPRE, T_HPRE, T_HHPRE, T_BIGLPRE,
	T_ZTPRE, T_JPRE,
	T_STOP,
	T_PTR, T_INT, T_UINT, T_ULLONG,
	T_LONG, T_ULONG,
	T_SHORT, T_USHORT, T_CHAR, T_UCHAR,
	T_LLONG, T_SIZET, T_IMAX, T_UMAX, T_PDIFF, T_UIPTR,
	T_DBL, T_LDBL,
	T_NOARG,
	T_MAXSTATE
};

typedef int		(t_fmtcb)(int t, t_fmt *f, t_varg arg, char *buf);

extern int		iofmt_fmtpct(int t, t_fmt *f, t_varg arg, char *buf);
extern int		iofmt_fmts(int t, t_fmt *f, t_varg arg, char *buf);

#endif
