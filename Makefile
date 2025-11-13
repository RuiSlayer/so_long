NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MINILIBX = ./mlx_linux/libmlx.a
MLXFLAGS = -L$(MINILIBX) -lXext -lX11 -lm -lz
SRCS = move.c inicializations.c free_pointers.c main.c parcer_semantics.c parcer_syntax.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C ft_get_next_line
	$(MAKE) -C ft_printf
	$(MAKE) -C 42libft
	$(MAKE) -C mlx_linux
	$(CC) $(CFLAGS) $(OBJS) -I. ft_get_next_line/ft_get_next_line.a ft_printf/libftprintf.a 42libft/libft.a $(MINILIBX) $(MLXFLAGS) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) $(MLXFLAGS) -c $< -o $@

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