#include "eval.h"
#include "fmt.h"
#include "parse.h"
#include "write.h"
#include <string.h>
#include <alloca.h>

static void re_eval_fmt(t_farg *arg, t_fmt	*f, t_va_slist *va)
{
	char 	*c;
	t_pf	*func;

	va->lock = 0;
	while (arg)
	{
		resolve_arg(arg, va);
		arg = arg->next;
	}
	while (f)
	{
		func = g_pf[TIDX(f->end[-1])];
		if (func)
			func(f, va);
		c = f->end;
		f = f->next;
		if (f)
			outns(0, c, f->begin - c - 1);
	}
}

static int exec(t_parse res, t_fmt *f, t_farg *arg_begin, t_va_slist *va)
{
	t_pf		*func;

	f->param = arg_at_index(arg_begin, res.param);
	f->precisionarg = res.precision != -1 ? arg_at_index(arg_begin, res.precision) : NULL;
	f->widtharg = res.width != -1 ? arg_at_index(arg_begin, res.width) : NULL;
	func = g_pf[TIDX(f->end[-1])];
	if (func)
		return (func(f, va));
	else 
		return (0);
}

inline static void next_arg(t_farg **arg, t_farg *next)
{
	(*arg)->next = next;
	*next = (t_farg) {
		.idx = (*arg)->idx + 1,
		.type = NONE,
		.next = NULL
	};
	*arg = next;
}

inline static void next_fmt(t_fmt **begin, t_fmt **f, t_fmt *next)
{
	if (*begin)
		(*f)->next = next;
	else
		*begin = next;
	*f = next;
	(*f)->next = NULL;
}

void eval_fmt(int fd, char const *fmt, t_va_slist *va, uint32_t	idx) {
	char		*c;
	t_fmt		*f;
	t_fmt		*f_b;
	t_parse		res;
	t_farg		*arg;
	t_farg		arg_b;

	c = (char *)fmt;
	f_b = NULL;
	arg = &arg_b;
	arg_b = (t_farg) { .idx = 0, .type = NONE };
	while ((c = strchr(c, '%')))
	{
		if (!va->lock)
			outns(0, f_b ? f->end : (char *)fmt, c - (f_b ? f->end : fmt));
		next_fmt(&f_b, &f, alloca(sizeof(t_fmt)));
		res = parse(&c, f, &idx);
		res.max -= arg->idx;
		while (res.max-- > 0)
			next_arg(&arg, alloca(sizeof(t_farg)));
		if (exec(res, f, &arg_b, va) == -1 && !va->lock && (f_b = f))
			va->lock = 1;
	}
	if (va->lock)
		re_eval_fmt(&arg_b, f_b, va);
	outs(0, f->end);
}