CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE


all: s21_grep

s21_grep:
	@${CC} ${CFLAGS} s21_grep.c -o s21_grep

clean:
	@rm -rf s21_grep *.txt

valgrind: s21_grep
	@valgrind --leak-check=full --tool=memcheck --log-file=log.txt ./s21_grep s21_grep.c

cppcheck: s21_grep
	@cppcheck --enable=all --std=c11 --inconclusive --suppress=missingIncludeSystem *.c

rebuild: clean s21_grep