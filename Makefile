NAME = so_long.a
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRCS = main.c parcer.c free_pointers.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C ft_get_next_line
	$(MAKE) -C ft_printf
	$(MAKE) -C 42libft
	$(CC) $(CFLAGS) $(OBJS) -I. ft_get_next_line/ft_get_next_line.a ft_printf/libftprintf.a 42libft/libft.a -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C ft_get_next_line fclean
	$(MAKE) -C ft_printf fclean
	$(MAKE) -C 42libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re