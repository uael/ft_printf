#ifndef FT_PRINTF_EVAL_H
# define FT_PRINTF_EVAL_H

# include "arg.h"
# include <stdint.h>
# include <sys/types.h>

typedef struct	s_fmt
{
	t_farg			*param;
	uint8_t			flags;
	int32_t			width;
	t_farg			*widtharg;
	int32_t			precision;
	t_farg			*precisionarg;
	uint8_t			length;
	char 			*begin;
	char 			*end;
	struct s_fmt	*next;
}				t_fmt;

typedef struct  s_ctx
{
	t_va_slist		va;
	uint32_t		idx;
	void 			(*write)(struct s_ctx *ctx, char *s, size_t n);
	void			*write_data;
}				t_ctx;

void 			eval_fmt(char *fmt, t_ctx ctx);

#endif