NAME = philo

CC = cc 
CFLAGS = -Wall -Wextra -Werror

SRCS = src/main.c src/init.c src/utils.c src/routine.c src/monitor.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re