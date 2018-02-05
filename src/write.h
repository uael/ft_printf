#ifndef FT_PRINTF_WRITE_H
# define FT_PRINTF_WRITE_H

# include "eval.h"
# include <sys/types.h>

void outflush(t_ctx *ctx);
void outn(t_ctx *ctx, char *s, size_t n);

#endif