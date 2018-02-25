/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int	ft_vfprintf(t_stream *f, const char *fmt, va_list ap)
{
	(void)f;
	(void)fmt;
	(void)ap;
	return (-1);
}
