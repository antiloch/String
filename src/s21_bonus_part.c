#include "s21_string.h"

static char *buffer = s21_NULL;

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  buffer = (char *)malloc(sizeof(char) * (s21_strlen(str) + 1));
  char *start = buffer;
  while (*str != '\0') {
    if (*str > 96 && *str < 123) {
      *buffer = *str - 32;
    } else {
      *buffer = *str;
    }
    str++;
    buffer++;
  }
  *buffer = '\0';
  return start;
}

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) return s21_NULL;
  buffer = malloc(sizeof(char) * (s21_strlen(str) + 1));
  char *start = buffer;
  while (*str != '\0') {
    if (*str > 64 && *str < 91) {
      *buffer = *str + 32;
    } else {
      *buffer = *str;
    }
    str++;
    buffer++;
  }
  *buffer = '\0';
  return start;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  // src - куда вставляем
  // str - что вставляем
  if (str == s21_NULL) return s21_NULL;
  char *start = s21_NULL;
  if (src != s21_NULL) {
    if (s21_strlen(src) >= start_index) {
      s21_size_t length = s21_strlen(src) + s21_strlen(str);
      s21_size_t index = start_index + s21_strlen(str);
      buffer = (char *)malloc(sizeof(char) * (length + 1));
      start = buffer;
      for (s21_size_t i = 0; i < length; i++) {
        if ((i < start_index) || (i >= index)) {
          *buffer = *src;
          src++;
        } else {
          *buffer = *str;
          str++;
        }
        buffer++;
      }
      *buffer = '\0';
    }
  }
  return start;
}

char *const_reverse(const char *s, char *new_str) {
  int len = s21_strlen(s);
  for (size_t i = len; i > 0; i--) {
    *new_str = s[i];
    new_str++;
  }
  new_str -= (len - 1);
  return new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == s21_NULL) return s21_NULL;
  char *start = s21_NULL;
  char *str = s21_NULL;
  if ((trim_chars == start) || (s21_strlen(trim_chars) == 0)) {
    trim_chars = "";
  }
  if (s21_strlen(src) != 0) {
    int first_entry = 0, last_entry = 0, length = s21_strlen(src);
    first_entry = s21_strspn(src, trim_chars);
    str = (char *)malloc(sizeof(char) * (length + 1));
    last_entry = s21_strspn(const_reverse(src, str), trim_chars);
    free(str);
    buffer = (char *)malloc(sizeof(char) * (length + 1));
    start = buffer;
    for (int i = 0; i < (length - last_entry); i++) {
      if (i < first_entry) {
        src++;
      } else {
        *buffer = *src;
        buffer++;
        src++;
      }
    }
    *buffer = '\0';
  } else {
    buffer = (char *)malloc(sizeof(char) * 1);
    *buffer = *src;
    start = buffer;
  } 
  return start;
}