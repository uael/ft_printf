# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/25 00:42:42 by alucas-           #+#    #+#              #
#    Updated: 2018/02/25 00:42:42 by alucas-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
WCFLAGS = -Werror -Wextra -Wall
CFLAGS = $(WCFLAGS) -O2
PRINTF=test $(VERBOSE)$(TRAVIS) || printf
CC ?= gcc

INC_PATH = include
SRC_PATH = src
OBJ_PATH = obj

SRC_NAME = \
  cty/isdigit.c \
  io/fmt/eval.c io/fmt/fmtd.c io/fmt/fmtm.c io/fmt/fmtpct.c io/fmt/fmts.c \
  io/fmt/fmtxp.c io/fmt/parse.c io/fmt/type.c io/asprintf.c io/dprintf.c \
  io/fprintf.c io/fwrite.c io/printf.c io/snprintf.c io/sprintf.c io/stderr.c \
  io/stdio.c io/stdout.c io/vasprintf.c io/vdprintf.c io/vfprintf.c \
  io/vprintf.c io/vsnprintf.c io/vsprintf.c io/fflush.c \
  lib/error.c lib/wctomb.c \
  str/bzero.c str/memcpy.c str/memset.c str/strchr.c str/strlen.c str/strnlen.c

OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
INC = $(addprefix -I, $(INC_PATH))
DEP = $(OBJ:%.o=%.d)

all: $(NAME)

$(NAME): $(3DE) $(OBJ)
	@$(PRINTF) "%-25s" "$(NAME): lib"
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@$(PRINTF) "\r\x1b[25C\x1b[0K\x1b[32m✔\x1b[0m\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(PRINTF) "\r\x1b[0K%-25s%s" "$(NAME): lib" $<
	@$(CC) $(CFLAGS) $(INC) -MMD -MP -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(dir $(OBJ))

clean:
	@rm -rf $(OBJ_PATH)
	@$(PRINTF) "%-25s\033[32m✔\033[0m\n" "$(NAME): $@"

fclean: clean
	@rm -f $(NAME)
	@$(PRINTF) "%-25s\033[32m✔\033[0m\n" "$(NAME): $@"

re: fclean all

test: all
	@./test.sh libftprintf

-include $(DEP)

.PHONY: all, $(NAME), clean, fclean, re, test
