# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pratanac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/06 10:57:59 by pratanac          #+#    #+#              #
#    Updated: 2022/05/06 10:58:01 by pratanac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = 	1_utils.c \
		2_config.c \
		3_free_philo.c \
		4_routine.c \
		5_check_die.c \
		philo.c

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
