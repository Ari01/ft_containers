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

sanitize:	main.cpp
			$(CC) $(CFLAGS) -D STD=0 -g -D SANITIZE=1 $^ -o $(NAME)
			$(CC) $(CFLAGS) -D STD=1 -g -D SANITIZE=1 $^ -o std

time:		main.cpp
			$(CC) $(CFLAGS) -D STD=0 -D TIME=1 $^ -o $(NAME)
			$(CC) $(CFLAGS) -D STD=1 -D TIME=1 $^ -o std


#debug:		$(OBJS)
#			$(CC) $(CFLAGS) -g -fsanitize=address $^ -o $@

#.cpp.o:
#			$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME) .*.swp ft std sanitize stdout ftout time diff_output

re:			fclean all

.PHONY:		all re clean fclean


