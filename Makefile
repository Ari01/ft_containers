NAME =		ft
STD =		std

SRCS =		MapTest.cpp \
			VectorTest.cpp \
			main.cpp

OBJS =		$(SRCS:.cpp=.o)

CC =		c++

CFLAGS =	-Wall -Wextra -Werror -std=c++98 

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(STD):		$(OBJS)
			$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

.cpp.o:
			$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(<:.cpp=.o)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME) .*.swp ft std stdout ftout diff_output

re:			fclean all

.PHONY:		all re clean fclean


