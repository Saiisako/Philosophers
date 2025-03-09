NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra -g #-fsanitize=address #-fsanitize=thread
RM = rm -rf

SRCS	=	main.c\
			free.c\
			init.c\
			utils.c\
			death.c\
			routines.c\
			one_philo.c\
			routine_orders.c\

OBJS = $(SRCS:.c=.o)

TARGET = $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)

.c.o:
	$(CC) $(FLAGS) -c -o $@ $<

all: $(NAME)

clean:
	@$(RM) $(OBJS)
	@echo "files erased successfully"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
