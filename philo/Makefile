# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smishos <smishos@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/26 14:19:00 by smishos           #+#    #+#              #
#    Updated: 2025/05/22 15:09:32 by smishos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread -g
INCLUDE = -I ./libft
SRCS = src/philo_main.c \
	src/cleanup.c \
	src/init.c \
	src/monitor.c \
	src/parsing.c \
	src/routine.c \
	src/simulation.c \
	src/utils.c \
	src/utils2.c

OBJ_DIR = objects
OBJS = $(addprefix $(OBJ_DIR)/,  $(SRCS:.c=.o))
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) -pthread

$(LIBFT):
	@$(MAKE) -C ./libft

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C ./libft

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: clean fclean re all