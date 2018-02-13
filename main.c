#include "ft_printf.h"

int main() {
  char *lol;

  ft_asnprintf(&lol, "I love %s", "unicorns");
  ft_printf("%% %s\n", lol);
}