NAME = rubik

SRCS = src/cube src/moves src/rotate src/solver src/generate_db main

INC = src/includes
CFLAGS = -Wall -Werror -Wextra -std=c++1y -stdlib=libc++ -lsqlite3
CC = clang++
SRCS := $(SRCS:%=%.cpp)
OBJS := $(SRCS:%.cpp=%.o)


all: $(NAME)
	@echo $(SRCS) $(OBJS) $(INC) $(CFLAGS) $(CC)

$(NAME): $(SRCS)
	@echo "\033[0;33m[ + ] COMPILING\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS) -I$(INC)