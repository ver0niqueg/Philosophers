NAME = philo

SRCS_DIR = ./srcs/

CC = cc
RM = rm -f
CFLAGS = -Werror -Wall -Wextra

SRCS = $(SRCS_DIR)/

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(NAME)

fclean: clean
			$(RM) $(NAME)

re: flcean all

.PHONY: all clean fclean re