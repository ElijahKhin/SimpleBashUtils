# --- PROJECT S21_CAT ---
NAME = s21_grep

HEADERS = $(NAME).h

SRC = flagsParsing.c findPattern.c

PREREQ = $(HEADERS) Makefile ../s21_common/s21_common.a

OBJ_FOLDER = obj
OBJ = $(SRC:%.c=$(OBJ_FOLDER)/%.o)

CC = gcc
FLAGS = -std=c11 -Wextra -Wall -I.

# --- TESTING S21_CAT ---
TCC = g++
TESTS = $(NAME)_tests.cc
TESTS_BIN = tests_bin_$(NAME)
GCOV_REPORT_NAME = tests_coverage_$(NAME)

# --- COLORS FOR A GOOD-LOOKING ASSEMBLING ---
GREEN = \033[32m
YELLOW = \033[0;33m
RED = \033[0;31m
GRAY = \033[2;37m
CURSIVE = \033[3m
NO_COLOR = \x1b[0m
RESET = \033[0m

# --- JUST TRASH --- 
GCOV_TRASH = $(GCOV_REPORT_NAME) $(GCOV_REPORT_NAME).info *.gcda *.gcno report  *.gch
OTHER_TRASH = obj *.a a.out .*.swp .DS_Store $(NAME) units $(TESTS_BIN) file_with_tests_trash py_res.csv unx_full_coverage_combo.csv

all: s21_common $(NAME)

$(NAME): $(OBJ_FOLDER) $(OBJ) main.c
	@$(CC) $(FLAGS) $(OBJ) main.c ../s21_common/s21_common.a -o $@
	@printf "\n$(CURSIVE)$(GREEN)$(NAME)$(RESET)$(CURSIVE) is ready to launch 💃🕺$(RESET)\n"

s21_common:
	@make -C ../s21_common/
.PHONY: s21_common

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(OBJ_FOLDER)/%.o: %.c $(PREREQ)
	@$(CC) -c $(FLAGS) $< -o $@

clean_gcov:
	@make clean_gcov -C ../s21_common/
	@rm -rf  $(GCOV_TRASH)
.PHONY: clean_gcov

fclean: clean_gcov
	@make fclean -C ../s21_common/
	@echo "$(RED)Cleaning $(NAME) & executable..."
	@rm -rf $(OTHER_TRASH)
	@echo "$(GRAY)$(CURSIVE)---$(NAME) staff is completely cleaned!\n$(RESET)"
.PHONY: fclean

re: fclean all
.PHONY: re

unx_full_coverage_combo.csv: py_script

py_script: all
	python3 cat_test_script.py

tests: all
	@make tests -C ../s21_common/
	@$(TCC) -std=c++17 -I. $(TESTS) $(OBJ) ../s21_common/s21_common.a -lgtest -lgtest_main -pthread -o $(TESTS_BIN)
	./$(TESTS_BIN)
.PHONY: test

show_tests_result: tests
	@./$(TESTS_BIN)
.PHONY: launch_test_bin

leaks: tests
	@make leaks -C ../s21_common/
	@leaks -quiet --atExit -- ./$(TESTS_BIN)
.PHONY: leaks

correct_format:
	@make correct_format -C ../s21_common/
	@clang-format -i $(SRC) $(TESTS) $(HEADERS)
.PHONY: correct_format

check_format:
	@make check_format -C ../s21_common/
	@clang-format --dry-run --Werror $(SRC) $(TEST) $(HEADES)
.PHONY: check_format
	
report/index.html: tests
	@make report/index.html -C ../s21_common/
	@$(TCC) -std=c++17 -Wno-deprecated -lgtest --coverage $(TESTS) $(SRC) ../s21_common/s21_common.a -o $(GCOV_REPORT_NAME)
	@./$(GCOV_REPORT_NAME)
	@lcov --no-external --no-recursion -c --directory . -o $(GCOV_REPORT_NAME).info
	@genhtml -o report $(GCOV_REPORT_NAME).info

open_gcov_report: report/index.html $(TESTS)
	@make open_gcov_report -C ../s21_common/
	@open report/index.html
.PHONY: open_gcov_report
