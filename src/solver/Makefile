# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kpereira <kpereira@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/11 16:07:35 by kpereira      #+#    #+#                  #
#    Updated: 2021/04/11 16:07:35 by kpereira      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRC = solver.cpp

OBJ_DIR = ../../obj

all: compile

compile:
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC) -I .
	@mv $(SRC:%.cpp=%.o) $(OBJ_DIR)
