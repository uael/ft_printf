/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib/wctomb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:44:14 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 14:29:11 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

#define IS_CODEUNIT(c) ((unsigned)(c) - 0xdf80 < 0x80)

int	ft_wctomb(char *s, wchar_t wc)
{
	if (!s)
		return (1);
	if ((unsigned)wc < 0x80)
	{
		*s = (char)wc;
		return (1);
	}
	else if (MB_CUR_MAX == 1)
	{
		if (!IS_CODEUNIT(wc))
		{
			errno = EILSEQ;
			return (-1);
		}
		*s = (char)wc;
		return (1);
	}
	else if ((unsigned)wc < 0x800)
	{
		*s++ = (char)(0xc0 | (wc >> 6));
		*s = (char)(0x80 | (wc & 0x3f));
		return (2);
	}
	else if ((unsigned)wc < 0xd800 || (unsigned)wc - 0xe000 < 0x2000)
	{
		*s++ = (char)(0xe0 | (wc >> 12));
		*s++ = (char)(0x80 | ((wc >> 6) & 0x3f));
		*s = (char)(0x80 | (wc & 0x3f));
		return (3);
	}
	else if ((unsigned)wc - 0x10000 < 0x100000)
	{
		*s++ = (char)(0xf0 | (wc >> 18));
		*s++ = (char)(0x80 | ((wc >> 12) & 0x3f));
		*s++ = (char)(0x80 | ((wc >> 6) & 0x3f));
		*s = (char)(0x80 | (wc & 0x3f));
		return (4);
	}
	errno = EILSEQ;
	return (-1);
}