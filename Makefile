NAME = test.out
SRCS = test.c filter.c foreach.c iter.c map.c range.c reduce.c list.c
OBJS = $(SRCS:.c=.o)

CC = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: $(NAME) all clean fclean re
