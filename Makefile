NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -I mlx #-g3 -fsanitize=address
LDFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

HEADERS = inc/cub3d.h #inc/get_next_line.h 

SRCS_DIR = src/

OBJS_DIR = objs/

SRCS_NAME = main.c


OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re