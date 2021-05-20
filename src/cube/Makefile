# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kpereira <kpereira@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/11 15:58:10 by kpereira      #+#    #+#                  #
#    Updated: 2021/04/11 15:58:10 by kpereira      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRC =	cube.cpp \
		moves.cpp \
		rotate.cpp

OBJ_DIR = ../../obj

all: compile

compile:
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(SRC) -I .
	@mv $(SRC:%.cpp=%.o) $(OBJ_DIR)
