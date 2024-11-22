NAME = philo

SRCS_DIR = ./srcs/
LIBFT_DIR = ./libft/

LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
RM = rm -f
CFLAGS = -Werror -Wall -Wextra

SRCS = $(SRCS_DIR)/

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT): $(MAKE) -C $(LIBFT_DIR)

clean:
			$(RM) $(NAME)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
			$(RM) $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean

re: flcean all

.PHONY: all clean fclean re