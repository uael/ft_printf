#!/usr/bin/env bash

OK="\033[32m[✔]\033[0m"
ERROR="\033[31m[✖]\033[0m"

RED='\033[0;31m'
CYAN='\033[0;36m'
RESET='\033[0m'
PURPLE='\033[0;35m'
YELLOW='\033[0;33m'

TMP_EXEC=$(mktemp)
TMP_ERR=$(mktemp)
LIBFTPRINTF=$1
FLAGS=$2

failed=0

function pad {
  S="$1"
  line='                                 '
  printf "%s %s" "$S" "${line:${#S}}"
}

function san_asnprintf {
	$CC -w -o "$TMP_EXEC" $FLAGS -DFORMAT="$1" -Iinclude -xc - -L . -l${LIBFTPRINTF#$"lib"} 2> /dev/tty << EOF
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include "ft_printf.h"

int main() {
	char *ft_printf_out;
	ssize_t ft_printf_return;

	ft_printf_return = ft_asprintf(&ft_printf_out, FORMAT);

	dprintf(1, "%zu:", ft_printf_return);
	write(1, ft_printf_out, ft_printf_return);
	free(ft_printf_out);
	return 0;
}
EOF
	$TMP_EXEC
}

function asnprintf {
	$CC -w -o $TMP_EXEC $FLAGS -DFORMAT="$1" -Iinclude -xc - -L . -l${LIBFTPRINTF#$"lib"} 2> /dev/tty << EOF
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include "ft_printf.h"

int main() {
	char *ft_printf_out;
	char *printf_out;
	ssize_t ft_printf_return;
	ssize_t printf_return;

	ft_printf_return = ft_asprintf(&ft_printf_out, FORMAT);
	printf_return = asprintf(&printf_out, FORMAT);

	dprintf(1, "%zu:", ft_printf_return);
	dprintf(2, "%zu:", printf_return);
	write(1, ft_printf_out, ft_printf_return);
	write(2, printf_out, printf_return);
	free(ft_printf_out);
	free(printf_out);
	return 0;
}
EOF
	$TMP_EXEC
}

function exec_printf {
	local impl=$1
	local name=$2
	local arg=$3

	echo -en "$YELLOW$(pad "$name")$RESET"
	local ft_printf_raw=$($impl "$arg" 2> $TMP_ERR)
	local printf_raw=$(<$TMP_ERR)
	if [[ $impl == san_* ]]; then
		if [[ -z $printf_raw ]]; then
			echo -e "$OK"
		else
			echo -e "$ERROR"
			failed=1
			echo "$printf_raw"
		fi
	else
		if [[ $ft_printf_raw == $printf_raw ]]; then
			echo -e "$OK"
		else
			echo -e "$ERROR"
			failed=1
			local ft_printf_return=${ft_printf_raw%%\:*}
			local ft_printf_out=${ft_printf_raw#*\:}
			local printf_return=${printf_raw%%\:*}
			local printf_out=${printf_raw#*\:}

			echo -e "====$PURPLE ftprintf $RESET===="
			echo -e ret $CYAN "$ft_printf_return" $RESET
			echo "$ft_printf_out"
			echo -e "=====$PURPLE printf $RESET====="
			echo -e ret $CYAN "$printf_return" $RESET
			echo "$printf_out"
			echo "=================="
		fi
	fi
}

function exec_tests {
	local impl=$1

	for test in test/*; do
		while read p; do
			IFS=':' read -r name format <<< "$p"
			if [[ $name != san_* || ! -z $SAN ]]; then
				exec_printf "$impl" "$(basename $test): $name" "$format"
			fi
		done < $test
	done
}

if [[ -z $IMPL ]]; then
	IMPL="asnprintf"
fi

for impl in $IMPL; do
	echo -e "$RED==> $impl <==\n $RESET"
	exec_tests $impl
done

rm -f $TMP_EXEC
rm -f $TMP_ERR

exit $failed