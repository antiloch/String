#include "s21_sprintf.h"

#include "s21_string.h"

int s21_sprintf(char *output_sting, const char *input_formated_string, ...) {
  char *start_pointer = output_sting;
  va_list(input_arguments);
  va_start(input_arguments, input_formated_string);

  while (*input_formated_string != '\0') {
    if (*input_formated_string == '%') {
      input_formated_string++;
      format_str format_specifiers = {0, 0, 0, 0, 0, 0, -1, 0, 0};
      parser(&input_formated_string, &input_arguments, &format_specifiers);
      format_to_str(format_specifiers, &input_arguments, &output_sting);
    }

    else {
      *output_sting = *input_formated_string;
      input_formated_string++;
      output_sting++;
    }
  }

  *output_sting = '\0';
  va_end(input_arguments);

  return (int)s21_strlen(start_pointer);
}

int parser(const char **input_formated_string, va_list *input_arguments,
           format_str *format_specifiers) {
  add_flags(input_formated_string, format_specifiers);
  add_width(input_formated_string, format_specifiers, input_arguments);
  add_precision(input_formated_string, format_specifiers, input_arguments);
  add_length(input_formated_string, format_specifiers);
  int error =
      check_and_add_specificator(input_formated_string, format_specifiers);

  return error;
}

void add_flags(const char **input_formated_string,
               format_str *format_specifiers) {
  if (s21_strspn(*input_formated_string, "+- 0") > 0) {
    int len = (int)s21_strspn(*input_formated_string, "+- 0");
    for (; len > 0; len--) {
      if (**input_formated_string == '+')
        format_specifiers->plus = 1, format_specifiers->flag = 1;
      if (**input_formated_string == '-')
        format_specifiers->minus = 1, format_specifiers->flag = 1;
      if (**input_formated_string == ' ')
        format_specifiers->space = 1, format_specifiers->flag = 1;
      if (**input_formated_string == '0')
        format_specifiers->zero = 1, format_specifiers->flag = 1;
      *input_formated_string = *input_formated_string + 1;
    }
  }
}

void add_width(const char **input_formated_string,
               format_str *format_specifiers, va_list *input_arguments) {
  char *buff = s21_NULL;
  char *start1 = s21_NULL;

  if (s21_strspn(*input_formated_string, "0123456789") > 0) {
    s21_size_t len = s21_strspn(*input_formated_string, "0123456789");
    buff = (char *)calloc(len + 1, sizeof(char));
    start1 = buff;
    s21_memcpy(buff, *input_formated_string, len);
    format_specifiers->width = s21_atoi(&buff);
    *input_formated_string = *input_formated_string + len;
  }

  if (**input_formated_string == '*') {
    format_specifiers->width = va_arg(*input_arguments, int);
    *input_formated_string = *input_formated_string + 1;
  }

  if (start1) free(start1);
}

void add_precision(const char **input_formated_string,
                   format_str *format_specifiers, va_list *input_arguments) {
  char *buff = s21_NULL;
  char *start2 = s21_NULL;

  if (**input_formated_string == '.') {
    *input_formated_string = *input_formated_string + 1;
    if (**input_formated_string == '*') {
      format_specifiers->precision = va_arg(*input_arguments, int);
      *input_formated_string = *input_formated_string + 1;
    } else {
      s21_size_t len = s21_strspn(*input_formated_string, "0123456789");
      buff = (char *)calloc(len + 1, sizeof(char));
      start2 = buff;
      s21_memcpy(buff, *input_formated_string, len);
      format_specifiers->precision = s21_atoi(&buff);
      *input_formated_string = *input_formated_string + len;
    }
  }

  if (start2) free(start2);
}

void add_length(const char **input_formated_string,
                format_str *format_specifiers) {
  if (**input_formated_string == 'l' || **input_formated_string == 'h' ||
      **input_formated_string == 'L') {
    format_specifiers->length = **input_formated_string;
    *input_formated_string = *input_formated_string + 1;
  }
}

int check_and_add_specificator(const char **input_formated_string,
                               format_str *format_specifiers) {
  int error = 0;
  if (s21_strspn(*input_formated_string, "cdifsu%") > 0) {
    format_specifiers->specificator = **input_formated_string;
    *input_formated_string = *input_formated_string + 1;
  } else
    error = 1;

  return error;
}

void format_to_str(format_str format_specifiers, va_list *input_arguments,
                   char **output_sting) {
  if (format_specifiers.specificator == 'f')
    handle_f(input_arguments, output_sting, format_specifiers);
  if (format_specifiers.specificator == 'd')
    handle_d(input_arguments, output_sting, format_specifiers);
  if (format_specifiers.specificator == 'i')
    handle_i(input_arguments, output_sting, format_specifiers);
  if (format_specifiers.specificator == 'u')
    handle_u(input_arguments, output_sting, format_specifiers);
  if (format_specifiers.precision == -1) format_specifiers.precision = 0;
  if (format_specifiers.specificator == 'c')
    handle_c(input_arguments, output_sting, format_specifiers);
  if (format_specifiers.specificator == 's')
    handle_s(input_arguments, output_sting, format_specifiers);
  if (format_specifiers.specificator == '%')
    handle_percent(output_sting, format_specifiers);
}

int s21_atoi(char **output_sting) {
  int len = s21_strspn(*output_sting, "0123456789");
  int result = 0;
  for (; len > 0; len--, *output_sting = *output_sting + 1)
    result += (**output_sting - '0') * pow(10, len - 1);
  return result;
}
