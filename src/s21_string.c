#include "s21_string.h"

#include "s21_errors.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (str[len] != '\0') len++;
  return len;
}

int s21_strcmp(const char *str1, const char *str2) {
  const unsigned char *c1 = (const unsigned char *)str1;
  const unsigned char *c2 = (const unsigned char *)str2;

  while (*c1 && *c2 == *c1) ++c1, ++c2;

  return *(const unsigned char *)c1 - *(const unsigned char *)c2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int i = 0;
  int result = 0;
  if (n == 0)
    result = 0;
  else if (str1[i] == '\0' && str2[i] == '\0')
    result = 0;
  else if (str1[i] == '\0')
    result = -str2[i];
  else if (str2[i] == '\0')
    result = str1[i];
  else {
    for (; str1[i] == str2[i] && i < (int)n; i++)
      ;
    if (str1[i] == '\0' || str2[i] == '\0' || i == (int)n)
      result = 0;
    else
      result = str1[i] - str2[i];
  }
  return result;
}

char *s21_strcpy(char *dest, const char *src) {
  int i = 0;
  while ((dest[i] = src[i]) != '\0') i++;
  return (char *)src;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int i = 0;
  while (src[i] != '\0' && i < (int)n) {
    dest[i] = src[i];
    i++;
  }
  return (char *)src;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int i = 0;
  while (str1[i] != '\0' && s21_strchr(str2, str1[i]) == s21_NULL) i++;
  return (s21_size_t)i;
}

//функция, которая переворачивает строку
void s21_reverse(char s[]) {
  int i, j;
  char c;
  for (i = 0, j = s21_strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

//реализация функции itoa (превращает число в строку)
void int_to_str(char s[], int n) {
  int i = 0, sign = n;
  if (sign < 0) {
    n *= (-1);
  }
  do {
    s[i] = n % 10 + '0';
    i++;
  } while ((n /= 10) > 0);
  if (sign < 0) {
    s[i] = '-';
    i++;
  }
  s[i] = '\0';
  s21_reverse(s);
}

char *s21_strerror(int errnum) {
  static char res[120] = {0};
  s21_memset(res, 0, 120);
  if (errnum >= 0 && errnum <= MAX_NUM) {
    s21_strcpy(res, error_list[errnum]);
  } else {
    char num[20];
    char error[100] = "Unknown error: ";
    int_to_str(num, errnum);
    s21_strcat(res, error);
    s21_strcat(res, num);
  }
  return res;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  int i = 0;
  while (str1[i] != '\0' && s21_strchr(str2, str1[i]) == s21_NULL) i++;
  return s21_strlen((char *)str1 + i) ? (char *)str1 + i : s21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  int i = 0, flag = 0;
  char *res = s21_NULL;
  while (str[i++] != '\0')
    if (str[i] == c) flag = i;
  if (s21_strlen((char *)str + flag)) {
    if (flag == 0)
      ;
    else
      res = (char *)str + flag;
  } else if (c == '\0') {
    res = "";
  }
  return res;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t n = 0;
  const char *p = s21_NULL;

  for (; *str1; str1++, n++) {
    for (p = str2; *p && *p != *str1; p++) {
    }
    if (!*p) break;
  }

  return n;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  int i = 0;
  while (i < (int)n) {
    ((char *)str)[i] = c;
    i++;
  }
  return str;
}

char *s21_strcat(char *dest, const char *src) {
  int i = 0, j = 0;
  while (dest[i] != '\0') i++;
  while ((dest[i++] = src[j++]) != '\0')
    ;
  dest[i] = '\0';
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int i = 0, j = 0;
  while (dest[i] != '\0') i++;
  while ((dest[i++] = src[j++]) != '\0' && j < (int)n)
    ;
  dest[i] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  int i = 0;
  int flag = 0;
  char *result = s21_NULL;

  while (*(str + i)) {
    if (*(str + i) == (char)c) {
      flag = 1;
      result = (char *)(str + i);
      break;
    }
    i++;
  }

  if (!flag && *(str + i) == c) result = (char *)(str + i);

  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *csrc = (char *)src;
  char *cdest = (char *)dest;
  for (int i = 0; i < (int)n; i++) {
    cdest[i] = csrc[i];
  }
  return cdest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *l1 = (char *)dest;
  char *l2 = (char *)src;

  if (dest != s21_NULL && src != s21_NULL) {
    s21_size_t i = 0;
    if (l1 > l2) {
      i = n;
      while (i--) *(l1 + i) = *(l2 + i);
    } else {
      i = 0;
      while (i++ < n) *(l1 + (i - 1)) = *(l2 + (i - 1));
    }
  }

  return l1;
}

char *s21_strstr(const char *haystack, const char *needle) {
  int flag = 0;
  char *ptr = (char *)haystack;
  while (*haystack != '\0' && flag == 0) {
    if ((*haystack == *needle) && s21_checks(haystack, needle))
      flag = 1;
    else
      haystack++;
  }
  return flag ? (char *)haystack : ((int)s21_strlen(needle) ? s21_NULL : ptr);
}

static char *pretoken = s21_NULL;

char *s21_strtok(char *str, const char *delim) {
  if (str == s21_NULL) str = pretoken;
  char *ptr = str;
  if (str != s21_NULL) {
    int i = (int)s21_strspn(str, delim);
    if (i >= (int)s21_strlen(str))
      ptr = s21_NULL;
    else
      ptr = str + i;
    if (ptr != s21_NULL) {
      char *end = s21_strpbrk(ptr, delim);
      if (end != s21_NULL) {
        if ((int)s21_strlen(end) != (int)s21_strspn(end, delim))
          pretoken = end + 1;
        else
          pretoken = s21_NULL;
        i = s21_strlen(str) - s21_strlen(end);
        str[i] = '\0';
      } else {
        pretoken = s21_NULL;
      }
    }
  } else {
    ptr = s21_NULL;
  }
  return ptr;
}

int s21_checks(const char *s, const char *t) {
  int flag = 0;
  while (*s && *t) {
    if (*s != *t) flag = 1;
    s++;
    t++;
  }
  return flag ? 0 : (*t == '\0');
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *nullptr = s21_NULL;
  for (int i = 0; i < (int)n; i++) {
    if (((char *)str)[i] == (char)c && nullptr == s21_NULL)
      nullptr = (void *)str + i;
  }
  return nullptr;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int i = 0, res = 0;
  while (i < (int)n && res == 0) {
    if (((char *)str1)[i] != ((char *)str2)[i])
      res += ((char *)str1)[i] - ((char *)str2)[i];
    i++;
  }
  return res;
}
