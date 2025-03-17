NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -I mlx #-g3 -fsanitize=address
LDFLAGS = -Lmlx -lmlx -lX11 -lXext -lm

HEADERS = inc/cub3d.h inc/get_next_line.h 

SRCS_DIR = src/

OBJS_DIR = objs/

SRCS_NAME = main.c \
			get_next_line.c \
			get_next_line_utils.c \
			err_exit.c \
			free.c \
			utils.c \
			valid_map.c \
			struct_map_check.c \
			raycasting.c \
			ft_split.c \
			type_identifier.c \
			type_identifier2.c \
			utils2.c \
			ft_split_color.c \
			initialization.c \
			initialization2.c \
			movements.c \
			movements2.c \
			set_wall_textures.c \
			set_gun_textures.c \
			set_textures.c \
			minimap.c \
			draw.c \
			draw2.c \


OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	# $(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re