#ifndef FT_PRINTF_WRITE_BUFFER_H
# define FT_PRINTF_WRITE_BUFFER_H

# include "eval.h"
# include <sys/types.h>

typedef struct {
	ssize_t	nb;
	char	*buffer;
	size_t	len;
} buffer_wdata;

void bufferflush(t_ctx *ctx);
void buffern(t_ctx *ctx, char *s, size_t n);
void bufferr(t_ctx *ctx, char s, size_t n);

#endif