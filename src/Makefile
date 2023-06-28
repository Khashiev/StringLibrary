FLAGS = -Werror -Wall -Wextra -std=c11

all: s21_string

s21_string:
	gcc $(FLAGS) s21_string.c -o s21_string

test:
	gcc $(FLAGS) -fsanitize=address $(FLAGS) s21_string.c unittests.c -lcheck -lm -lrt -lpthread -lsubunit -o test

sanTest: s21_string.c unittests.c
	gcc -c s21_string.c unittests.c 
	gcc s21_string.o unittests.o -lcheck -lm -lrt -lpthread -lsubunit -fsanitize=address


rebuild: clean test 
	./test

clean: 
	rm test