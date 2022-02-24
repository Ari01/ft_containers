NAME =		ft

#SRC =		

#OBJS =		

CC =		c++

CFLAGS =	-Wall -Wextra -Werror -std=c++98 

all:		$(NAME)

$(NAME):	main.cpp
			$(CC) $(CFLAGS) -D STD=0 -D DEBUG=0 $^ -o $@

std:		main.cpp
			$(CC) $(CFLAGS) -D STD=1 -D DEBUG=0 $^ -o $@

debug:		main.cpp
			$(CC) $(CFLAGS) -D STD=0 -D DEBUG=1 $^ -o $(NAME)
			$(CC) $(CFLAGS) -D STD=1 -D DEBUG=1 $^ -o std

#debug:		$(OBJS)
#			$(CC) $(CFLAGS) -g -fsanitize=address $^ -o $@

#.cpp.o:
#			$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME) .*.swp debug std

re:			fclean all

.PHONY:		all re clean fclean


