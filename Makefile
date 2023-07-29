# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hemottu <hemottu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/13 14:07:03 by hemottu           #+#    #+#              #
#    Updated: 2023/07/29 15:04:38 by hemottu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -rf
SRC = 	main.c \
		utils.c \
		parsing.c \
		time.c \
		mutex.c \
		write.c \
		threads.c \
		actions.c

OBJ = $(SRC:.c=.o)

all: $(NAME) 

$(NAME): $(OBJ)
	$(CC) $(SRC) $(CFLAGS) -pthread -o $(NAME) 

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	all re clean fclean