NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror  -fsanitize=thread -g 

GREEN = \033[0;32m
ORANGE = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

SRC = \
	main.c \
	create_data_philos.c \
	create_mutex.c \
	create_threads.c \
	free_resources.c \
	ft_error_msg.c \
	ft_my_atoi.c \
	get_current_time.c \
	monitor_routine.c \
	parse_argements.c \
	print_status.c \
	routine_philos.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Execution$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(RED)clean$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)fclean$(RESET)"

re: fclean all
	@echo "$(ORANGE)Remaking$(RESET)"

.PHONY: all clean fclean re

