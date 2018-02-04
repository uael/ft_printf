#include "fmt.h"
#include "write.h"

int get_arg(t_farg *arg, t_types type, t_va_slist *ap);


int	fmt(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmts(t_fmt *fmt, t_va_slist *ap)
{
	TRY(get_arg(fmt->param, PTR, ap));
	outs(0, fmt->param->value.p);
	return (0);
}

int	fmtsu(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmtp(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmtd(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmtdu(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmti(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmto(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmtou(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmtu(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmtuu(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmtx(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmtxu(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmtc(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}

int	fmtcu(t_fmt *fmt, t_va_slist *ap)
{
	return (0);
}