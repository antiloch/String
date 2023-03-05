#include "../s21_sprintf.h"
#include "../s21_string.h"

void handle_s(va_list *input, char **str, format_str fs) {
  char *s = va_arg(*input, char *);
  s21_size_t len = s21_strlen(s);
  int precision = (int)len;
  if (fs.precision > 0 && fs.precision < (int)len) precision = fs.precision;
  int res_width = precision;
  if (!fs.minus) width_add(res_width, str, fs);
  while (*s != '\0' && precision > 0) {
    **str = *s;
    *str = *str + 1;
    s++;
    precision--;
  }
  if (fs.minus) width_add(res_width, str, fs);
}
