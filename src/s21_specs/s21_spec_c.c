#include "../s21_sprintf.h"
#include "../s21_string.h"

void handle_c(va_list *input, char **str, format_str fs) {
  if (!fs.minus) width_add(1, str, fs);
  wchar_t s = va_arg(*input, wchar_t);
  **str = s;
  *str = *str + 1;
  if (fs.minus) width_add(1, str, fs);
}
