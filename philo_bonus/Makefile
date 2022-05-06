NAME = philo_bonus

SRC = 	1_utils.c \
	3_config.c \
	4_routine.c \
	5_check_die.c \
	2_utils_bonus.c \
	philo_bonus.c

OBJS = $(SRC:.c=.o)

CC = gcc

FLAG = -Wall -Werror -Wextra

%.o: %.c philosophers.h
	@echo "Compiling : $<"
	@$(CC) $(FLAG) -c $< -o $@

$(NAME): $(OBJS)
		@echo "Creating : $@"
		@$(CC) $(OBJS) -o $(NAME) -lpthread

all: $(NAME)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all
