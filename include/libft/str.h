/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/str.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:18:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STR_H
# define LIBFT_STR_H

# include <stdint.h>
# include <stdlib.h>
# include <sys/types.h>

# include "cty.h"

extern void		ft_bzero(void *ptr, size_t n);
extern void		*ft_memcpy(void *dst, void const *src, size_t n);
extern void		*ft_memset(void *b, int c, size_t len);
extern char		*ft_strchr(char const *s, int c);
extern size_t	ft_strlen(char const *str);
extern size_t	ft_strnlen(char const *str, size_t size);

#endif
