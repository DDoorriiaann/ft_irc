NAME = ircserv
CPP = g++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = srcs
SRC = 	Classes/Client/Client.cpp\
		Classes/Server/CheckClientStatus.cpp\
		Classes/Server/Init.cpp\
		Classes/Server/Run.cpp\
		Classes/Server/Server.cpp\
		Classes/Channel/Channel.cpp\
		Utils/checkPort.cpp\
		main.cpp\

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
