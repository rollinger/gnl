# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: prolling <prolling@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/29 08:03:01 by prolling          #+#    #+#              #
#    Updated: 2021/05/29 08:15:54 by prolling         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
FLAGS = -Wall -Wextra -Werror
CC = gcc
LIB = ar rc

ifdef BUFFER_SIZE
	BUFFER_SIZE = "-D BUFFER_SIZE=$(BUFFER_SIZE)"
else
	BUFFER_SIZE = "-D BUFFER_SIZE=32"
endif

sources = get_next_line.c get_next_line_utils.c
headers = get_next_line.h

$(NAME): clean
	$(CC) -c -Wall -Wextra -Werror $(BUFFER_SIZE) $(sources) $(headers)
	ar rc $(NAME) *.o
	ranlib $(NAME)
	rm -f *.o *.gch

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY:	all clean fclean re
