NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra -g -fsanitize=thread 
RM = rm -rf

SRCS	=	main.c philo_utils.c parsing.c\

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
