#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = S21_NULL;
  char *hst = (char *)haystack;

  for (; *hst != '\0' && !res; hst++) {
    if (*hst == *needle) {
      res = hst;

      char *ndl = (char *)needle;
      for (; *ndl != '\0'; ndl++, hst++) {
        if (*hst != *ndl) {
          res = S21_NULL;
        }
      }
    }
  }

  return res;
}