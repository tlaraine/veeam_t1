SRCS		= main.cpp
NAME		= programm
CC			= g++

RM			= rm -f

$(NAME):	
			$(CC) $(SRCS)  -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(NAME)

re:			clean all

.PHONY:		all programm
