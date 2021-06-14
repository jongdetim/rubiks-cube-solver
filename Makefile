# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: asulliva <asulliva@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/11 17:24:28 by asulliva      #+#    #+#                  #
#    Updated: 2021/04/11 17:24:28 by asulliva      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = rubik

SRC_DIR = src
DIRS =	cube \
		solver \
		database

SRC_DIRS = $(foreach dir, $(DIRS), $(addprefix $(SRC_DIR)/, $(dir)))
INC = $(foreach dir, $(SRC_DIRS), $(addprefix -I ,$(dir)))
OBJ_DIR = obj

SRC_FILES =$(foreach dir, $(SRC_DIRS), $(shell find "$(dir)" -name "*.h" -o -name "*.cpp")) 

CFLAGS = -Wall \
		-Werror \
		-Wextra \
		-std=c++1y \
		-stdlib=libc++

CC = clang++

all: $(NAME)

$(NAME): $(SRC_FILES) main.cpp main.h
	@echo "\033[0;33m[ + ] Preparing classes\033[0m"
	@for dir in $(SRC_DIRS); do \
    	make --silent -C "$${dir}"; \
	done
	@echo "\033[0;33m[ + ] Compiling $(NAME)\033[0m"
	@$(CC) $(CFLAGS) -o $(OBJ_DIR)/main.o -c main.cpp $(INC)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_DIR)/*.o $(INC)
	@echo "\033[0;32m[ + ] Compilation of $(NAME) complete\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;31m[ - ] Removed object files\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m[ - ] Removed $(NAME)\033[0m"

re: fclean all

test: all
	./$(NAME)
