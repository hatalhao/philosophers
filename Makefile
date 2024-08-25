NAME = philo

CC = cc

CFLAGS = -g3 -Werror -Wall -Wextra -pthread -fsanitize=address

#SRC = $(wildcard src/*.c)
SRC = $(filter-out src/philo_state.c, $(wildcard src/*.c))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
