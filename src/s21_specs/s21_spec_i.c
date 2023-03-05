#include "../s21_sprintf.h"
#include "../s21_string.h"

void handle_i(va_list *input, char **str, format_str fs) {
  long int num = va_arg(*input, long int);
  if (fs.length != 'l') num = (int)num;
  if (fs.length == 'h') num = (short int)num;
  int res_width = width_calculate(num, fs);
  if (!fs.minus) width_add(res_width, str, fs);
  if (fs.width != 0 || fs.precision != 0 || num != 0 || fs.flag != 0) {
    znak(str, num, fs);
    precision_add(num, str, fs);
    s21_itoa(str, num);
  }
  if (fs.minus) width_add(res_width, str, fs);
}

void handle_d(va_list *input, char **str, format_str fs) {
  long int num = va_arg(*input, long int);
  if (fs.length != 'l') num = (int)num;
  if (fs.length == 'h') num = (short int)num;
  int res_width = width_calculate(num, fs);
  if (!fs.minus) width_add(res_width, str, fs);
  if (fs.width != 0 || fs.precision != 0 || num != 0 || fs.flag != 0) {
    znak(str, num, fs);
    precision_add(num, str, fs);
    s21_itoa(str, num);
  }
  if (fs.minus) width_add(res_width, str, fs);
}

int width_calculate(long int num, format_str fs) {
  int num_width = get_num_width(num);
  if (num >= 0 && fs.plus) num_width++;
  return fs.precision > num_width ? fs.precision + (fs.plus && num >= 0)
                                  : num_width;
}

void precision_add(long int num, char **str, format_str fs) {
  int target_precision = fs.precision;
  while (target_precision > get_num_width(num)) {
    **str = '0';
    *str = *str + 1;
    target_precision--;
  }
}

void width_add(int res_width, char **str, format_str fs) {
  int target_width = fs.width;
  while (target_width > res_width) {
    if (fs.zero)
      **str = '0';
    else
      **str = ' ';
    *str = *str + 1;
    target_width--;
  }
}

int get_num_width(long int num) {
  int result = 0;
  if (num < 0) {
    num *= -1;
    result++;
  }
  if (num == 0) result++;
  for (; num > 0; result++) num /= 10;
  return result;
}

void znak(char **str, long int num, format_str fs) {
  if (num >= 0 && fs.plus) {
    **str = '+';
    *str = *str + 1;
  }

  if (num >= 0 && fs.space) {
    **str = ' ';
    *str = *str + 1;
  }

  if (num < 0) {
    **str = '-';
    *str = *str + 1;
  }
}

void s21_itoa(char **str, long int num) {
  if (num < 0) num *= -1;

  long int buff = num, i = 0;
  while ((buff /= 10) > 0) i++;
  buff = num;
  for (; i >= 0; i--, *str = *str + 1)
    **str = (long int)(buff / pow(10, i)) % 10 + '0';
}
