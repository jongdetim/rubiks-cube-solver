# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tide-jon <tide-jonstudent.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/31 20:23:41 by tide-jon      #+#    #+#                  #
#    Updated: 2021/07/31 20:23:41 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		:=	rubik
FILES		:=	cube moves rotate solver database visualizer main
INC_DIR		:=	./src/includes/
SFML_DIR	:=	~/.brew/include
INC_FILES	:=	argparse cube database main solver visualizer
INC			:=	$(addprefix $(INC_DIR),$(INC_FILES:%=%.hpp))
CFLAGS		:=	-Wall -Wextra -Werror -std=c++17 -Ofast
LDIR		:=	~/.brew/lib/
LIBS		:=	-lsqlite3 -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -framework OpenGL -framework GLUT
CC			:=	clang++
OBJ_DIR		:=	./obj/
SRCS		:=	$(FILES:%=src/%.cpp)
OBJS		:=	$(addprefix $(OBJ_DIR),$(FILES:%=%.o))

all: $(NAME)

changed: $(SRCS) Makefile $(INC)
	@echo "\033[0;33m[ + ] CREATING OBJECT FILES\033[0m"
	@touch changed

$(NAME): $(INC) $(OBJS)
	@$(CC) $(CFLAGS) -L $(LDIR) $(LIBS) -o $(NAME) $(OBJS)
	@echo "\033[0;32m[ + ] COMPILATION OF $(NAME) COMPLETE\033[0m"

$(OBJ_DIR)%.o : src/%.cpp Makefile $(INC) | changed
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $(word 1,$^) -o $@ -I $(INC_DIR) -I $(SFML_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f changed
	@echo "\033[0;31m[ - ] REMOVED OBJECT FILES\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m[ - ] REMOVED $(NAME)\033[0m"

re: fclean all

.PHONY: clean fclean all re
