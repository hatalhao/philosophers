NAME = philo

CC = cc

CFLAGS = -Werror -Wall -Wextra -pthread # -g3 -fsanitize=thread

SRC = $(wildcard src/*.c)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@make clean

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
