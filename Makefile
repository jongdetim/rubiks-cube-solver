# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tide-jon <tide-jon@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/31 20:23:41 by tide-jon      #+#    #+#                  #
#    Updated: 2021/07/31 20:23:41 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	rubik
FILES		=	cube moves rotate solver generate_db visualizer main
INC			=	src/includes/ -I ~/.brew/Cellar/sfml/2.5.1_1/include
CFLAGS		=	-Wall -Wextra -Werror -std=c++17 -Ofast
LDIR		=	~/.brew/Cellar/sfml/2.5.1_1/lib/
LIBS		=	-lsqlite3 -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-network -framework OpenGL -framework GLUT
CC			=	clang++
SRCS		=	$(FILES:%=src/%.cpp)
OBJS		=	$(FILES:%=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	# @echo "\033[0;33m[ + ] -CREATING OBJECT FILES\033[0m"
	# @$(CC) $(CFLAGS) -c $(SRCS) -I $(INC_DIR)
	# @mkdir -p $(OBJ_DIR)
	# @mv $(OBJS) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -L $(LDIR) $(LIBS) -o $(NAME) $(OBJS)
	@echo "\033[0;32m[ + ] COMPILATION OF $(NAME) COMPLETE\033[0m"

%.o : src/%.cpp src/includes/%.hpp
				$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;31m[ - ] REMOVED OBJECT FILES\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m[ - ] REMOVED $(NAME)\033[0m"

re: fclean all

.PHONY: clean fclean all re
