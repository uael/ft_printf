#ifndef FT_PRINTF_ARG_H
# define FT_PRINTF_ARG_H

# include <stdint.h>
# include <sys/types.h>
# include <stdarg.h>

typedef struct	s_va_slist
{
	va_list		ap;
	size_t		idx;
	uint8_t		lock;
}	t_va_slist;

union	u_arg
{
	uintmax_t	i;
	long double f;
	void		*p;
};

typedef enum e_types {
	NONE,
	PTR,
	INT,
	LONG,
	LLONG,
	SIZET,
	IMAX,
	DBL,
	LDBL
}			t_types;

typedef struct		s_farg
{
	t_types			type;
	union u_arg		value;
	size_t idx;
	struct s_farg	*next;
} t_farg;

int resolve_arg(t_farg *arg, t_va_slist *ap);
int get_arg(t_farg *arg, t_types type, t_va_slist *ap);
t_farg *arg_at_index(t_farg *begin, size_t pos);

#endif