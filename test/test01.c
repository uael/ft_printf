#include <stdio.h>
#include <assert.h>
#include "ft_printf.h"

static short flags(char **it)
{
	short flag;

	if (FIDX(**it) < 0 || (size_t)FIDX(**it) >
		(sizeof(g_flags) / sizeof(*g_flags)))
		return (0);
	if ((flag = g_flags[FIDX(**it)]))
	{
		++*it;
		if ((flag & PF_H && **it == 'h') || (flag & PF_L && **it == 'l'))
		{
			flag <<= 1;
			++*it;
		}
		return (flag | flags(it));
	}
	return (0);
}

int test_flags_01(void)
{
	char *s = "h#hhl ll0-++---987-";
	short f = flags(&s);

	assert(f & PF_H);
	assert(f & PF_HASH);
	assert(f & PF_HH);
	assert(f & PF_L);
	assert(f & PF_SPACE);
	assert(f & PF_LL);
	assert(f & PF_MINUS);
	assert(f & PF_ZERO);
	assert(f & PF_PLUS);
	assert(f == (PF_H | PF_HASH | PF_HH | PF_L | PF_SPACE | PF_LL | PF_MINUS | PF_ZERO | PF_PLUS));
	assert(*s == '9');
	return (0);
}

int	main(void)
{
	test_flags_01();
	printf("%44d", 10);
	return (0);
}