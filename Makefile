# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 19:04:12 by bchafi            #+#    #+#              #
#    Updated: 2025/02/23 11:54:53 by bchafi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror #-fsanitize=address -g
PRINTF = ft_printf/ft_printf.c ft_printf/ft_printf_utils.c

SOURCES_C = \
	client.c utils/ft_atoi.c $(PRINTF)
SOURCES_S = \
	server.c $(PRINTF)
OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_S = $(SOURCES_S:.c=.o)

SOURCES_C_B = \
	bonus/client_bonus.c utils/ft_atoi.c $(PRINTF)
SOURCES_S_B = \
	bonus/server_bonus.c $(PRINTF)
OBJECTS_C_B = $(SOURCES_C_B:.c=.o)
OBJECTS_S_B = $(SOURCES_S_B:.c=.o)

all : client server

client : $(OBJECTS_C)
	$(CC) $(OBJECTS_C) -o $@

server : $(OBJECTS_S)
	$(CC) $(OBJECTS_S) -o $@

bonus : client server client_bonus server_bonus

client_bonus : $(OBJECTS_C_B)
	$(CC) $(OBJECTS_C_B) -o $@

server_bonus : $(OBJECTS_S_B)
	$(CC) $(OBJECTS_S_B) -o $@

.c : .o minitalk.h bonus/minitalk_bonus.h
	$(CC) -c $< -o $@

clean :
	rm -rf $(OBJECTS_C) $(OBJECTS_S) $(OBJECTS_C_B) $(OBJECTS_S_B)

fclean : clean
	rm -rf server client client_bonus server_bonus

re : all clean
.PHONY:	clean