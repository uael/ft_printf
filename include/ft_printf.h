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
# include <sys/types.h>

ssize_t	ft_printf(char const *fmt, ...);
ssize_t	ft_vprintf(char const *fmt, va_list ap);
ssize_t	ft_dprintf(int fd, char const *fmt, ...);
ssize_t	ft_vdprintf(int fd, char const *fmt, va_list ap);
ssize_t	ft_asnprintf(char **out, char const *fmt, ...);
ssize_t	ft_vasnprintf(char **out, char const *fmt, va_list ap);

#endif
