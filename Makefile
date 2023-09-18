NAME = fdf

SRCS = 	fdf.c \
		fdf_draw_helper.c \
		fdf_utils.c \
		minilibx_helper.c \
		ft_hexstr_to_int.c \
		fdf_read_file.c \
		fdf_color.c \
		fdf_bonus.c \
		fdf_bonus_utils.c \
		fdf_bonus_utils_rotate.c \

OBJS = $(SRCS:.c=.o)

CC = cc

LINKS = -I libft -L libft -I /usr/local/include -L /usr/local/lib  -l mlx -l ft  -framework OpenGL -framework Appkit

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	$(CC) -o $@ $(OBJS) $(FLAGS) $(LINKS)

%.o: %.c
	$(CC) -c $(FLAGS) -o $@ $<

.PHONY: clean fclean bonus re

clean:
	rm -f $(SRCS:.c=.o) $(BONUS:.c=.o)

fclean: clean
	rm -f $(NAME)

re: fclean all
