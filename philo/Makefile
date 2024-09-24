# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonim <jonim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/04 21:33:57 by jonim             #+#    #+#              #
#    Updated: 2023/07/16 17:37:25 by jonim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = philo
TARGET = $(NAME)

SRCS = main.c ph_atoi.c ph_init.c ph_cctv.c ph_exe.c ph_gt_cf.c ph_simul.c \
ph_join.c ph_free.c ph_odd.c ph_even.c

OBJS = $(SRCS:.c=.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $? -o $@

.PHONY : clean fclean re

clean :
	rm -rf $(OBJS)

fclean :
	make	clean
	rm -f	$(NAME)

re :
	make fclean
	make all