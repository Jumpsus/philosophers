NAME = philo

SRC = 	1_utils.c \
		2_config.c \
		3_free_philo.c \
		4_routine.c \
		5_check_die.c \
		philo.c

OBJS = $(SRC:.c=.o)

CC = gcc

#FLAG = -Wall -Werror -Wextra

FLAG = ""

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
