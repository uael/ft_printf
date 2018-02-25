/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_sprintf(char *s, const char *fmt, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, fmt);
	ret = ft_vsprintf(s, fmt, ap);
	va_end(ap);
	return (ret);
}
