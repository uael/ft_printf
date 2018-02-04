#include "parse.h"
#include <ctype.h>

uint32_t	atoio(char **it)
{
	int32_t i;

	i = 0;
	while (isdigit(**it) && i >= 0)
		i = i * 10 + *(*it)++ - '0';
	if (i < 0)
	{
		while (isdigit(**it))
			++*it;
		i = 0;
	}
	return (uint32_t)(i);
}

t_parse parse(char **it, t_fmt *f, uint32_t *idx)
{
	t_parse	res;

	f->begin = ++*it;
	if (isdigit(**it)) {
		res.param = atoio(it) - 1;
		if (*(*it)++ != '$') {
			*it = f->begin;
			res.param = -1;
		}
	} else
		res.param = -1;
	f->flags = parse_flags(it);
	res.width = parse_width(it, f, idx);
	res.precision = parse_precision(it, f, idx);
	f->length = parse_length(it);
	f->end = *it + 1;
	if (res.param == -1)
		res.param = (*idx)++;
	res.max = MAX(MAX(MAX(res.param, res.width), res.precision), 0);
	return (res);
}

uint8_t parse_flags(char **it)
{
	uint8_t flag;

	if (FIDX(**it) < 0 || (size_t)FIDX(**it) >
		(sizeof(g_flags) / sizeof(*g_flags)))
		return (0);
	if ((flag = g_flags[FIDX(**it)]))
	{
		++*it;
		return (flag | parse_flags(it));
	}
	return (0);
}

int32_t	parse_width(char **it, t_fmt *fmt, uint32_t *idx)
{
	fmt->width = 0;
	if (**it == '*')
	{
		fmt->width = -1;
		return isdigit(*++*it) ? atoio(it) - 1 : (*idx)++;
	}
	else if (isdigit(**it))
		fmt->width = atoio(it);
	return (-1);
}

int32_t parse_precision(char **it, t_fmt *fmt, uint32_t *idx)
{
	if (**it == '.')
	{
		++*it;
		if (**it == '*')
		{
			fmt->precision = -1;
			return isdigit(*++*it) ? atoio(it) - 1 : (*idx)++;
		}
		else if (isdigit(**it))
			fmt->precision = atoio(it);
	}
	else
		fmt->precision = -1;
	return (-1);
}

uint8_t parse_length(char **it)
{
	uint8_t flag;

	if (LIDX(**it) < 0 || (size_t)LIDX(**it) >
		(sizeof(g_elens) / sizeof(*g_elens)))
		return (0);
	if ((flag = g_elens[LIDX(**it)]))
	{
		++*it;
		if ((flag & PF_H && **it == 'h') || (flag & PF_L && **it == 'l'))
		{
			flag <<= 1;
			++*it;
		}
		return (flag || parse_length(it));
	}
	return (0);
}