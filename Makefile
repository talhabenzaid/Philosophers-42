NAME		= philo

SRCS		= philosophers.c parsing.c init.c routine.c


OBJS		= $(SRCS:%.c=%.o)

FLAGS		= -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS)  $(OBJS) -o $@

%.o: %.c philosophers.h
	cc $(FLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) 

re: fclean all