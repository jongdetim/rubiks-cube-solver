# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tide-jon <tide-jon@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/14 18:54:49 by tide-jon      #+#    #+#                  #
#    Updated: 2021/06/14 18:57:33 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRC =	generate_db.cpp \

OBJ_DIR = ../../obj

all: compile

compile:
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(SRC) -I .
	@mv $(SRC:%.cpp=%.o) $(OBJ_DIR)
