NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror


GREEN = \033[0;32m
ORANGE = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

SRC = ./main.c \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ../Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT)  -o $(NAME)
	@echo "$(GREEN)Execution$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -I./includes -I$(LIBFT_DIR) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(RED)clean$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RED)fclean$(RESET)"

re: fclean all
	@echo "$(ORANGE)Remaking$(RESET)"

.PHONY: all clean fclean re libft

