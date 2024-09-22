# --- PROJECT S21_COMMON ---
NAME = s21_common.a

HEADERS = s21_common.h

SRC = s21_strlen.c s21_isdigit.c s21_strlcpy.c s21_atoi.c s21_split.c \
			s21_itoa.c

PREREQ = $(HEADERS) Makefile

OBJ_FOLDER = obj
OBJ = $(SRC:%.c=$(OBJ_FOLDER)/%.o)

CC = gcc
FLAGS = -std=c11 -Wall -Wextra -Werror -I.

# --- TESTING S21_COMMON ---
TCC = g++
TESTS = s21_common_tests.cc
TESTS_BIN = tests_bin_s21_common
GCOV_REPORT_NAME = tests_coverage_s21_common


# --- COLORS FOR A GOOD-LOOKING ASSEMBLING ---
GREEN = \033[32m
YELLOW = \033[0;33m
RED = \033[0;31m
GRAY = \033[2;37m
CURSIVE = \033[3m
NO_COLOR = \x1b[0m

# --- JUST TRASH --- 
GCOV_TRASH = $(GCOV_REPORT_NAME) $(GCOV_REPORT_NAME).info *.gcda *.gcno report *.gch
OTHER_TRASH = obj *.a a.out .*.swp .DS_Store $(NAME) units $(TESTS_BIN) file_with_tests_trash

all: $(NAME)
.PHONY: all

$(NAME): $(OBJ_FOLDER) $(OBJ)
	@ar rc $@ obj/*	
	@ranlib $(NAME)
	@printf "$(CURSIVE)Compiling source files 🚀...  %s is successfully assembled! 🥂%-17s" $(NAME) ""

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(OBJ_FOLDER)/%.o: %.c $(PREREQ)
	@$(CC) -c $(FLAGS) $< -o $@
	@printf "$(CURSIVE)Compiling source files 🚀... $(YELLOW)%-13s ---> $(NO_COLOR)%17.33s ✅\r" $< $@

clean_gcov:
	@rm -rf  $(GCOV_TRASH)
.PHONY: clean_gcov

fclean: clean_gcov
	@echo "$(RED)Cleaning $(NAME) & executable..."
	@rm -rf $(OTHER_TRASH)
	@echo "$(GRAY)$(CURSIVE)---$(NAME) staff is completely cleaned!\n$(RESET)"
.PHONY: fclean

re: fclean all
.PHONY: re

tests: all
	@$(TCC) -std=c++17 $(TESTS) -L. $(NAME) -lgtest -lgtest_main -pthread -o $(TESTS_BIN)
.PHONY: test

leaks: tests
	@leaks -quiet --atExit -- ./$(TESTS_BIN)
.PHONY: leaks

correct_format:
	@clang-format -i $(SRC) $(TESTS) $(HEADERS)
.PHONY: correct_format

check_format:
	@clang-format --dry-run --Werror $(SRC) $(TEST) $(HEADES)
.PHONY: check_format
	
report/index.html: $(NAME)
	@$(TCC) -std=c++17 -Wno-deprecated -lgtest --coverage $(TESTS) $(SRC) -L. $(NAME) -o $(GCOV_REPORT_NAME)
	@./$(GCOV_REPORT_NAME)
	@lcov --no-external --no-recursion -c --directory . -o $(GCOV_REPORT_NAME).info
	@genhtml -o report $(GCOV_REPORT_NAME).info

open_gcov_report: report/index.html $(TESTS)
	@open report/index.html
.PHONY: open_gcov_report
