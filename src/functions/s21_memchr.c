#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *res = S21_NULL;
  char *ptr = (char *)str;

  for (s21_size_t i = 0; i < n && ptr && !res; i++, ptr++) {
    if (*ptr == c) {
      res = ptr;
    }
  }

  return res;
}