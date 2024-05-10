NAME = minishell

SRCS = src/main.c src/parsing/syntax.c src/parsing/split_request.c \
	   src/utils.c 

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror -lreadline -lncurses
all: libft  $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS)  -o  $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

libft:
	make -C libft 


clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft minilibx

