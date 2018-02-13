#ifndef FT_PRINTF_WRITE_OUT_H
# define FT_PRINTF_WRITE_OUT_H

# include "eval.h"
# include <sys/types.h>

typedef struct {
	ssize_t		nb;
	int			fd;
	char 		buf[4096];
	uint16_t	idx;
} out_wdata;

void outflush(t_ctx *ctx);
void outn(t_ctx *ctx, char *s, size_t n);
void outr(t_ctx *ctx, char s, size_t n);

#endif