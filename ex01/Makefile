NAME = RPN

CC = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp RPN.cpp

OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ) RPN.hpp
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)
clean :
	@rm -rf $(OBJ)
fclean : clean 
	@rm -rf $(NAME)
re : fclean all

