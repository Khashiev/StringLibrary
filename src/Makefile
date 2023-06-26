all: s21_string

s21_string:
	gcc $(FLAGS) s21_string.c -o s21_string

test:
	gcc s21_string.c unittests.c -lcheck -lm -lrt -lpthread -lsubunit -o test

rebuild: clean test 
	./test

clean: 
	rm test