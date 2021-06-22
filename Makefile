# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: asulliva <asulliva@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/11 17:24:28 by asulliva      #+#    #+#                  #
#    Updated: 2021/06/22 17:17:57 by asulliva      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	rubik
SRCS_FILES	=	cube moves rotate solver generate_db main
SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC			=	src/includes
CFLAGS		=	-Wall -Werror -Wextra -std=c++17
CC			=	clang++
OBJS 		:=	$(SRCS_FILES:%=%.o)
SRCS		=	$(addprefix $(SRC_DIR), $(SRCS_FILES))
SRCS 		:=	$(SRCS:%=%.cpp)
COBJ		=	$(addprefix $(OBJ_DIR), $(OBJS))
TEST_ARG	=	"U2"

all: $(NAME)

$(NAME): $(SRCS)
	@echo "\033[0;33m[ + ] -CREATING OBJECT FILES\033[0m"
	@$(CC) -c $(CFLAGS) $(SRCS) -I $(INC)
	@mkdir -p $(OBJ_DIR)
	@mv $(OBJS) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -lsqlite3 -o $(NAME) $(COBJ) -I $(INC)
	@echo "\033[0;32m[ + ] COMPILATION OF $(NAME) COMPLETE\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;31m[ - ] REMOVED OBJECT FILES\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m[ - ] REMOVED $(NAME)\033[0m"

re: fclean all

test: re
	./$(NAME) $(TEST_ARG)
