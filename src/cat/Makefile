NAME = s21_cat

SRC = s21_cat.c

PREREQ = $(SRC) s21_cat.h Makefile ../s21_common/s21_common.a

CC = gcc
FLAGS = -std=c11 -Werror -Wextra -Wall -I.

GREEN = \033[32m
YELLOW = \033[0;33m
RED = \033[0;31m
GRAY = \033[2;37m
CURSIVE = \033[3m
NO_COLOR = \x1b[0m
RESET = \033[0m


all: common $(NAME)

$(NAME): $(PREREQ) 
	@$(CC) $(FLAGS) $(SRC) -L. ../s21_common/s21_common.a -o $@
	@echo "----------------------------------------------------------\n"
	@printf "$(CURSIVE)Assembling $(NAME) ⚙️ ... $(GREEN)DONE! 🥂$(RESET)"
	@echo "\n"

common:
	@make -C ../s21_common/
.PHONY: s21_common

clean:
	@make clean -C ../s21_common/
	@rm -rf obj
.PHONY: clean

fclean: clean
	@make fclean -C ../s21_common/
	@rm -rf *.a a.out .*.swp *.*.gch .DS_Store test_bin a.out.dSYM $(NAME)
	@echo "$(GRAY)$(CURSIVE)---$(NAME) staff is completely cleaned!\n"

.PHONY: fclean

re: fclean all
.PHONY: re
