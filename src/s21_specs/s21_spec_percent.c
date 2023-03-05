#include "../s21_sprintf.h"
#include "../s21_string.h"

void handle_percent(char **str, format_str fs) {
  if (!fs.minus) width_add(1, str, fs);
  char s = '%';
  **str = s;
  *str = *str + 1;
  if (fs.minus) width_add(1, str, fs);
}
