NAME = common.a


SRC = s21_strlen.c s21_isdigit.c s21_strlcpy.c \
			s21_atoi.c s21_substr.c s21_split.c s21_itoa.c

OBJ_FOLDER = obj
OBJ = $(SRC:%.c=$(OBJ_FOLDER)/%.o)


CC = gcc
FLAGS = -Wall -Wextra -Werror -I.


GREEN = \033[32m
YELLOW = \033[0;33m
RED = \033[0;31m
GRAY = \033[2;37m
CURSIVE = \033[3m
NO_COLOR = \x1b[0m


.PHONY: all clean fclean re


all: $(NAME)

$(NAME): $(OBJ_FOLDER) $(OBJ)
	@ar rc $@ obj/*	
	@ranlib $(NAME)
	@printf "$(CURSIVE)Compiling source files 🚀...  %s is successfully assembled! 🥂%-17s" $(NAME) ""
	@echo "\n"

$(OBJ_FOLDER):
	@mkdir $(OBJ_FOLDER)

$(OBJ_FOLDER)/%.o: %.c common.h Makefile
	@$(CC) -c $(FLAGS) $< -o $@
	@printf "$(CURSIVE)Compiling source files 🚀... $(YELLOW)%-13s ---> $(NO_COLOR)%17.33s ✅\r" $< $@

clean:
	@echo "$(RED)Cleaning libft objects..."
	@rm -rf obj 
	@echo "$(GRAY)$(CURSIVE)---libft objects are cleaned!\n"

fclean: clean
	@echo "$(RED)Cleaning $(NAME) & executable..."
	@rm -rf *.a a.out .*.swp .DS_Store $(NAME) units
	@echo "$(GRAY)$(CURSIVE)---libft staff is completely cleaned!\n"

re: fclean all
