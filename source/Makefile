CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98
RM			= rm -f
SRC			= main.cpp
OBJ			= $(SRC:%.cpp=%.o)
NAME		= ft_containers
UNAME		:= $(shell uname)


.cpp.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

$(NAME):	${OBJ}
			@$(CC) $(CFLAGS) -D LIB=1 $(SRC) -o $(NAME)
			@./ft_containers 1 > std
			@$(CC) $(CFLAGS) -D LIB=0 $(SRC) -o $(NAME)
			@./ft_containers 1 > ft
			@diff std ft > diff

all:		${NAME}

clean:		
			@${RM} ${OBJ}
			@${RM} diff
			@${RM} std
			@${RM} ft

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re valfun subject