#include "../s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;

  char *ptr = (char *)str;
  while (*ptr != '\0') {
    len++;
    ptr++;
  }

  return len;
}