#include "../s21_sprintf.h"
#include "../s21_string.h"

void handle_f(va_list *input, char **str, format_str fs) {
  long double num = 0.0;
  if (fs.length != 'L')
    num = va_arg(*input, double);
  else
    num = va_arg(*input, long double);

  int res_width = width_calculate_f(num, fs);
  if (!fs.minus) width_add(res_width, str, fs);
  znak_f(str, num, fs);
  s21_ftos(str, num, fs);
  if (fs.minus) width_add(res_width, str, fs);
}

int width_calculate_f(long double num, format_str fs) {
  int num_width = get_float_width(num);
  if ((int)num != num) num_width++;
  if (fs.precision > -1) {
    if ((int)num == num) num_width++;
    num_width += fs.precision;
  } else
    num_width += 6;
  if (num >= 0 && fs.plus) num_width++;
  return num_width;
}

int get_float_width(long double num) {
  int result = 0;
  int int_num = (int)num;
  if (int_num < 0.0) {
    int_num *= -1;
    result++;
  }
  if (int_num == 0) result++;
  for (; int_num > 0; result++) int_num /= 10;
  return result;
}

void znak_f(char **str, long double num, format_str fs) {
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

void s21_ftos(char **str, long double num, format_str fs) {
  if (num < 0) num *= -1.;

  int buff = (int)num, i = 0, precision = 0;
  while ((buff /= 10) > 0) i++;
  buff = num;
  for (; i >= 0; i--, *str = *str + 1)
    **str = (int)(buff / pow(10, i)) % 10 + '0';

  if (fs.precision > -1)
    precision = fs.precision;
  else
    precision = 6;
  if (precision != 0) {
    **str = '.';
    *str = *str + 1;
  }
  long double after_point = num - (int)num;
  if (precision < 15) after_point += 0.0000000001;
  for (; i >= -precision; i--, *str = *str + 1) {
    after_point *= 10;
    int num_to_print = (int)after_point % 10;
    after_point = after_point - (int)after_point;
    int num_next_to_print = (long int)fmodl(after_point * 10., 10.);
    if (i == -precision && num_next_to_print > 4 && num_to_print < 9)
      **str = (num_to_print + 1) % 10 + '0';
    else
      **str = num_to_print + '0';
  }
}
