#ifndef S21_STRING_H_
#define S21_STRING_H_

#define S21_NULL ((void *)0)
typedef unsigned long s21_size_t;

s21_size_t s21_strlen(const char *str);
void *s21_memchr(const void *str, int c, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strrchr(const char *str, int c);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strerror(int errnum);
char *s21_strtok(char *str, const char *delim);

#endif  // S21_STRING_H_