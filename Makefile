NAME =		ft
STD =		std

SRCS =		MapTest.cpp \
			VectorTest.cpp \
			main.cpp

STDOBJS =	$(SRCS:.cpp=.o)

FTOBJS =	$(addprefix ft, $(STDOBJS))

CC =		c++

CFLAGS =	-Wall -Wextra -Werror -std=c++98 

all:		$(NAME)

$(NAME):	$(FTOBJS)
			$(CC) $(CFLAGS) -D STD=0 $^ -o $@

$(STD):		$(STDOBJS)
			$(CC) $(CFLAGS) -D STD=1 $^ -o $@

$(STDOBJS):	$(SRCS)
			$(CC) $(CFLAGS) -D STD=1 -c $^

$(FTOBJS):	$(SRCS)
			$(CC) $(CFLAGS) -D STD=0 -c $^

sanitize:	main.cpp $(STDOBJS) $(FTOBJS)
			$(CC) $(CFLAGS) -D STD=0 -g -D SANITIZE=1 $^ -o $(NAME)
			$(CC) $(CFLAGS) -D STD=1 -g -D SANITIZE=1 $^ -o $(STD)

time:		main.cpp $(STDOBJS) $(FTOBJS)
			$(CC) $(CFLAGS) -D STD=0 -D TIME=1 $^ -o $(NAME)
			$(CC) $(CFLAGS) -D STD=1 -D TIME=1 $^ -o $(STD)


#debug:		$(OBJS)
#			$(CC) $(CFLAGS) -g -fsanitize=address $^ -o $@

clean:
			rm -rf $(STDOBJS) $(FTOBJS)

fclean:		clean
			rm -rf $(NAME) .*.swp ft std map sanitize stdout ftout time diff_output

re:			fclean all

.PHONY:		all re clean fclean


