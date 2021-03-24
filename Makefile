CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g3
SANITIZE = -fsanitize=address
LINKERFLAG = -lm
SRCS = $(wildcard *.c) $(wildcard utils/*.c)
OBJS = $(SRCS:.c=.o)
MAIN = my_bsq

.PHONY = all clean fclean re

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(SANITIZE) -o $@ $(LINKERFLAG) $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(MAIN)

re: fclean all