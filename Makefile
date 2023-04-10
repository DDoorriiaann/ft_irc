NAME = ircserv
CPP = g++
CPPFLAGS = -g -Wall -Wextra -Werror -std=c++98 -pthread

SRCDIR = srcs
SRC = 	Classes/Client/Client.cpp\
		Classes/Server/Init.cpp\
		Classes/Server/Run.cpp\
		Classes/Server/Server.cpp\
		Classes/Channel/Channel.cpp\
		Classes/Server/Cmds/Private_msg/sendPrivateMsg.cpp\
		Classes/Server/Cmds/Nick/nick.cpp\
		Classes/Server/Cmds/Pass/passCmd.cpp\
		Classes/Server/Cmds/User/userCmd.cpp\
		Classes/Server/Cmds/Bot/botCmd.cpp\
		Classes/Server/Cmds/Kick/kick.cpp\
		Classes/Server/Cmds/Part/part.cpp\
		Classes/Server/Cmds/Mode/mode.cpp\
		Utils/checkPort.cpp\
		Utils/checkWhiteSpace.cpp\
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
