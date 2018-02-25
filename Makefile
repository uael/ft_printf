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

PROJECT ?= libftprintf
WFLAGS = -Werror -Wextra -Wall
WWFLAGS = $(WFLAGS) -Wpedantic -Wshadow -Wconversion -Wcast-align \
  -Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
  -Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
  -Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
  -Wredundant-decls -Wall -Werror -Wextra
RCFLAGS = $(WFLAGS) -O2 -fomit-frame-pointer
DCFLAGS = $(WFLAGS) -g3 -DDEBUG
SCFLAGS = $(DCFLAGS) -fsanitize=address,undefined -ferror-limit=5
CC ?= gcc

INC_PATH = include
SRC_PATH = src
OBJ_DIR ?= obj
OBJ_PATH ?= $(OBJ_DIR)/rel
3TH_PATH =

LIBS =
ifneq (,$(findstring dev,$(PROJECT)))
LIB_NAME = $(addsuffix .dev, $(LIBS))
else ifneq (,$(findstring san,$(PROJECT)))
LIB_NAME = $(addsuffix .san, $(LIBS))
else
LIB_NAME = $(LIBS)
endif
3TH_NAME =
SRC_NAME = \
  io/fmt/eval.c io/fmt/fmt_01.c io/fmt/parse.c io/fmt/type.c \
  io/asprintf.c io/dprintf.c io/fprintf.c io/fwrite.c io/printf.c \
  io/snprintf.c io/sprintf.c io/stderr.c io/stdio.c io/stdout.c io/vasprintf.c \
  io/vdprintf.c io/vfprintf.c io/vprintf.c io/vsnprintf.c io/vsprintf.c

3TH = $(addprefix $(3TH_PATH)/, $(3TH_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_NAME:.c=.o))
LNK = $(addprefix -L, $(3TH))
INC = $(addprefix -I, $(INC_PATH) $(addsuffix /include, $(3TH)))
LIB = $(addprefix -l, $(LIB_NAME))
DEP = $(OBJ:%.o=%.d)

PRINTF=test $(VERBOSE)$(TRAVIS) || printf

ifeq ($(OS), Windows_NT)
  CCFLAGS += -D WIN32
  ifeq ($(PROCESSOR_ARCHITECTURE), AMD64)
    CCFLAGS += -D AMD64
  else ifeq ($(PROCESSOR_ARCHITECTURE), x86)
    CCFLAGS += -D IA32
  endif
else
  UNAME_S = $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
    CCFLAGS += -D LINUX
  else ifeq ($(UNAME_S), Darwin)
    CCFLAGS += -D OSX
  endif
  UNAME_P = $(shell uname -p)
  ifeq ($(UNAME_P), unknown)
    UNAME_P = $(shell uname -m)
  endif
  ifeq ($(UNAME_P), x86_64)
    CCFLAGS += -D AMD64
  else ifneq ($(filter %86, $(UNAME_P)), )
    CCFLAGS += -D IA32
  else ifneq ($(filter arm%, $(UNAME_P)), )
    CCFLAGS += -D ARM
  endif
endif

all:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) &&) true
endif
	+$(MAKE) $(PROJECT).a "CFLAGS = $(RCFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

dev:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) dev &&) true
endif
	+$(MAKE) $(PROJECT).dev.a "PROJECT = $(PROJECT).dev" "CFLAGS = $(DCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/dev"

san:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) san &&) true
endif
	+$(MAKE) $(PROJECT).san.a "PROJECT = $(PROJECT).san" "CFLAGS = $(SCFLAGS)" \
	  "OBJ_PATH = $(OBJ_DIR)/san" "CC = clang"

mecry:
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) mecry &&) true
endif
	+$(MAKE) $(PROJECT).a "CFLAGS = $(WWFLAGS)" "OBJ_PATH = $(OBJ_DIR)/rel"

$(PROJECT).a: $(OBJ)
	ar -rc $(PROJECT).a $(OBJ)
	ranlib $(PROJECT).a
	@$(PRINTF) "%-20s\033[32m✔\033[0m\n" "$(PROJECT): lib"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(shell dirname $@)
	@$(PRINTF) "\r%-20s$<\n" "$(PROJECT):"
	$(CC) $(CFLAGS) $(CCFLAGS) $(INC) -MMD -MP -c $< -o $@
	@$(PRINTF) "\033[A\033[2K"

clean:
	rm -f $(OBJ) $(DEP)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/dev%)
	rm -f $(OBJ:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%) $(DEP:$(OBJ_DIR)/rel%=$(OBJ_DIR)/san%)
	@$(PRINTF) "%-20s\033[32m✔\033[0m\n" "$(PROJECT): $@"

fclean: clean
ifneq ($(3TH_NAME),)
	+$(foreach 3th,$(3TH_NAME),$(MAKE) -C $(3TH_PATH)/$(3th) fclean &&) true
endif
	test -d $(OBJ_DIR) && find $(OBJ_DIR) -type d | sort -r | xargs rmdir || true
	rm -f $(PROJECT){,.san,.dev}.a
	@$(PRINTF) "%-20s\033[32m✔\033[0m\n" "$(PROJECT): $@"

re: clean all

test: all
	./test.sh $(NAME)

-include $(DEP)

ifndef VERBOSE
 ifndef TRAVIS
.SILENT:
 endif
endif

.PHONY: all, dev, san, mecry, $(PROJECT).a, clean, fclean, re, test
