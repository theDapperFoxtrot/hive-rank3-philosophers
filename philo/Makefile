# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 14:19:00 by smishos           #+#    #+#              #
#    Updated: 2025/05/23 20:10:07 by smishos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread -g
SRCS = src/philo_main.c \
	src/cleanup.c \
	src/init.c \
	src/monitor.c \
	src/parsing.c \
	src/routine.c \
	src/simulation.c \
	src/utils.c \
	src/utils2.c \
	src/ft_atoi.c

OBJ_DIR = objects
OBJS = $(addprefix $(OBJ_DIR)/,  $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -pthread

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all