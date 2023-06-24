#include <string.h>  // delete

#include "../s21_string.h"
s21_size_t s21_strspn(const char *str1, const char *str2);

char *s21_strtok(char *str, const char *delim) {
  static char *tmp = S21_NULL;
  if (str) tmp = str;

  if (tmp) {
    str = tmp + s21_strspn(tmp, delim);
    tmp = str + strcspn(str, delim);  // change

    if (*tmp != '\0') {
      *tmp = '\0';
      tmp++;
    }
  }

  return *str != '\0' ? str : S21_NULL;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  s21_size_t ptr = 0;

  for (s21_size_t i = 0; str1[i]; i++) {
    ptr = res;
    for (s21_size_t j = 0; str2[j]; j++) {
      if (str1[i] == str2[j]) {
        res++;
        break;
      }
    }
    if (ptr == res) break;
  }

  return res;
}