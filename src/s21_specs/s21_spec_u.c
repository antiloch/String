#include "../s21_sprintf.h"
#include "../s21_string.h"

void handle_u(va_list *input, char **str, format_str fs) {
  unsigned long int num = va_arg(*input, unsigned long int);
  if (fs.length != 'l') num = (unsigned int)num;
  if (fs.length == 'h') num = (unsigned short int)num;
  int res_width = width_calculate_u(num, fs);
  if (!fs.minus) width_add(res_width, str, fs);
  precision_add_u(num, str, fs);
  s21_utoa(str, num);
  if (fs.minus) width_add(res_width, str, fs);
}

int width_calculate_u(unsigned long int num, format_str fs) {
  int num_width = get_num_width_u(num);
  if (fs.plus) num_width++;
  return fs.precision > num_width ? fs.precision : num_width;
}

void precision_add_u(unsigned long int num, char **str, format_str fs) {
  int target_precision = fs.precision;
  while (target_precision > get_num_width_u(num)) {
    **str = '0';
    *str = *str + 1;
    target_precision--;
  }
}

int get_num_width_u(unsigned long int num) {
  int result = 0;
  if (num == 0) result++;
  for (; num > 0; result++) num /= 10;
  return result;
}

void s21_utoa(char **str, unsigned long int num) {
  unsigned long int buff = num;
  int i = 0;
  while ((buff /= 10) > 0) i++;
  buff = num;
  for (; i >= 0; i--, *str = *str + 1)
    **str = (unsigned long int)(buff / pow(10, i)) % 10 + '0';
}
