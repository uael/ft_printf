/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io/asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#             */
/*   Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <locale.h>
#include <limits.h>

#include "libft/io.h"

int	main(void)
{
	setlocale(LC_ALL, "");
	printf("%d\n", ft_printf("%s", ""
		"lkdsfjgkl;jsdfgkljskldfjglksdfgkjsldfkjglksdfjgkjlsdfkjgklsjdklfgjksldfg"
		"dsfkljgklsdjfgksdfjglkjsdklfgjklsdfjlgkjsdflkjglksdfjglkjslkdfjglksdjfgklj"
		"sdfklgjklsdfgjlksdfjgkljsdlkfgjlksdfjklgjkdflsjglkjfsdklgjlkfsdjgkljsdfklgj"
		"dklsfjgklsdjfglkjsdklfgjlksdfjglkjsdflkgjklsdfjgkljdfsklgjlksdfjgklsdfg"));
	return (0);
}
