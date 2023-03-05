#ifndef S21_SPRINTF_H_
#define S21_SPRINTF_H_

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct {
  int minus;
  int zero;
  int space;
  int plus;
  int flag;
  int width;
  int precision;
  char length;
  char specificator;
} format_str;

// general
int parser(const char **format, va_list *input, format_str *fs);
void format_to_str(format_str fs, va_list *input, char **str);
void width_add(int res_width, char **str, format_str fs);
void add_flags(const char **input_formated_string,
               format_str *format_specifiers);
void add_width(const char **input_formated_string,
               format_str *format_specifiers, va_list *input_arguments);
void add_precision(const char **input_formated_string,
                   format_str *format_specifiers, va_list *input_arguments);
void add_length(const char **input_formated_string,
                format_str *format_specifiers);
int check_and_add_specificator(const char **input_formated_string,
                               format_str *format_specifiers);

// d
void handle_d(va_list *input, char **str, format_str fs);

// i && d
void handle_i(va_list *input, char **str, format_str fs);
int width_calculate(long int num, format_str fs);
void precision_add(long int num, char **str, format_str fs);
void znak(char **str, long int num, format_str fs);
int get_num_width(long int num);
void s21_itoa(char **str, long int num);

// u
void handle_u(va_list *input, char **str, format_str fs);
int width_calculate_u(unsigned long int num, format_str fs);
void precision_add_u(unsigned long int num, char **str, format_str fs);
int get_num_width_u(unsigned long int num);
void znak_u(char **str, format_str fs);
void s21_utoa(char **str, unsigned long int num);

// c
void handle_c(va_list *input, char **str, format_str fs);

// s
void handle_s(va_list *input, char **str, format_str fs);

// f
void handle_f(va_list *input, char **str, format_str fs);
int width_calculate_f(long double num, format_str fs);
int get_float_width(long double num);
void s21_ftos(char **str, long double num, format_str fs);
void znak_f(char **str, long double num, format_str fs);

// %
void handle_percent(char **str, format_str fs);

#endif  // S21_SPRINTF_H_