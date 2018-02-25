/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vsnprintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VSNPRINTF_H
# define VSNPRINTF_H

# include "ft_printf.h"

typedef struct	s_cookie
{
	char		*s;
	size_t		n;
}				t_cookie;

#endif
