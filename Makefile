NAME = philo

SRCS_DIR = ./srcs/

CC = cc
RM = rm -f
CFLAGS = -Werror -Wall -Wextra

SRCS = $(SRCS_DIR)/main.c					\
			$(SRCS_DIR)/init_simulation.c	\
			$(SRCS_DIR)/philo_actions.c		\
			$(SRCS_DIR)/philo_routine.c		\
			$(SRCS_DIR)/philo_monitoring.c	\
			$(SRCS_DIR)/utils_1.c			\
			$(SRCS_DIR)/utils_2.c			\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re