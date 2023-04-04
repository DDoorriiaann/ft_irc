NAME = ircserv
CPP = g++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = srcs
SRC = main.cpp Classes/Client/Client.cpp Classes/Server/Server.cpp Server/manaTcpServer.cpp Utils/checkPort.cpp
OBJ = $(addprefix $(SRCDIR)/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
