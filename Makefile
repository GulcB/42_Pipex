NAME = pipex
BONUS_NAME = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./gnl
LIBFT_DIR = ./libft 
LIBFT = $(LIBFT_DIR)/libft.a

SRC = pipex.c utils.c 
BONUS_SRC = bonus/ft_free_bonus.c bonus/pipex_bonus.c bonus/utils_bonus.c \
			gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o) 

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

bonus: $(LIBFT) $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -L$(LIBFT_DIR) -lft -o $(BONUS_NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME) $(BONUS_NAME) $(OBJ) $(BONUS_OBJ)

re: fclean all bonus

rmfile: clean
	$(RM) infile outfile output

.PHONY: all clean fclean re rmfile
