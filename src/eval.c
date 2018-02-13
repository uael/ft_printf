#include "eval.h"
#include "fmt.h"
#include "parse.h"
#include <string.h>
#include <alloca.h>

static void re_eval_fmt(t_farg *arg, t_fmt	*f, t_ctx *ctx)
{
	char 	*c;
	t_pf	*fn;

	ctx->va.lock = 0;
	while (arg)
	{
		resolve_arg(arg, &ctx->va);
		arg = arg->next;
	}
	while (f)
	{
		fn = g_pf[TIDX(f->end[-1])];
		if (fn)
			fn(f, ctx);
		c = f->end;
		f = f->next;
		if (f)
			ctx->write(ctx, c, f->begin - c - 1);
	}
}

static int exec(t_parse *res, t_fmt *f, t_farg *arg_begin, t_ctx *ctx)
{
	t_pf		*fn;

	if (!f->param)
		f->param = arg_at_index(arg_begin, res->param);
	if (!f->precisionarg)
		f->precisionarg = res->precision != -1 ? arg_at_index(arg_begin, res->precision) : NULL;
	if (!f->widtharg)
		f->widtharg = res->width != -1 ? arg_at_index(arg_begin, res->width) : NULL;
	fn = g_pf[TIDX(f->end[-1])];
	if (fn)
		return (fn(f, ctx));
	else 
		return (0);
}

inline static void next_arg(t_farg **arg, t_farg *next, t_fmt *fmt, t_parse *res)
{
	(*arg)->next = next;
	*next = (t_farg) {
		.idx = (*arg)->idx + 1,
		.type = NONE,
		.next = NULL
	};
	if (next->idx == res->param)
		fmt->param = next;
	if (next->idx == res->precision)
		fmt->precisionarg = next;
	if (next->idx == res->width)
		fmt->widtharg = next;
	*arg = next;
}

inline static void next_fmt(t_fmt **begin, t_fmt **f, t_fmt *next)
{
	if (*begin)
		(*f)->next = next;
	else
		*begin = next;
	*next = (t_fmt){
		.next = NULL,
		.param = NULL,
		.precisionarg = NULL,
		.widtharg = NULL
	};
	*f = next;
}

void eval_fmt(char *fmt, t_ctx ctx) {
	char		*c;
	t_fmt		*f;
	t_fmt		*f_b;
	t_parse		res;
	t_farg		*arg;
	t_farg		arg_b;

	c = fmt;
	f_b = NULL;
	arg = &arg_b;
	arg_b = (t_farg) { .idx = 0, .type = NONE };
	while ((c = strchr(c, '%')))
	{
		if (!ctx.va.lock)
			ctx.write(&ctx, f_b ? f->end : fmt, c - (f_b ? f->end : fmt));
		next_fmt(&f_b, &f, alloca(sizeof(t_fmt)));
		res = parse(&c, f, &ctx.idx);
		res.max -= arg->idx;
		while (res.max-- > 0)
			next_arg(&arg, alloca(sizeof(t_farg)), f, &res);
		if (exec(&res, f, &arg_b, &ctx) == -1 && !ctx.va.lock && (f_b = f))
			ctx.va.lock = 1;
	}
	if (ctx.va.lock)
		re_eval_fmt(&arg_b, f_b, &ctx);
}