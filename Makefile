NAME =		ft
STD =		std
PROVIDED =	provided

DIR =		test/src

SRCS =		$(DIR)/MapTest.cpp \
			$(DIR)/VectorTest.cpp \
			$(DIR)/StackTest.cpp \
			$(DIR)/main.cpp

OBJS =		$(SRCS:.cpp=.o)

CC =		c++

CFLAGS =	-Wall -Wextra -Werror -std=c++98 -g 

INCLUDE =	-Icontainers -Icontainers/utils -Itest/include

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDE) $^ -o $@

$(STD):		$(OBJS)
			$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDE) $^ -o $@

$(PROVIDED):$(DIR)/main2.cpp
			$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@

.cpp.o:
			$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDE) -c $< -o $(<:.cpp=.o)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME) $(STD) $(PROVIDED) .*.swp stdout ftout diff_output

re:			fclean all

.PHONY:		all re clean fclean


