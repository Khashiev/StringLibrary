FLAGS=-Wall -Wextra -Werror -std=c11

all: s21_string

s21_string:
	gcc $(FLAGS) s21_string.c -o s21_string

test:
	gcc s21_string.c unittests.c -lcheck -lm -lcrypto -o test

rebuild: clear all
