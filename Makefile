NAME = ircserv
BOTNAME = bot
CPP = g++
CPPFLAGS = -g -Wall -Wextra -Werror -std=c++98

SRCDIR = srcs
SRC = 	Classes/Client/Client.cpp\
		Classes/Server/Init.cpp\
		Classes/Server/Run.cpp\
		Classes/Server/Server.cpp\
		Classes/Server/ChannelsManagement.cpp\
		Classes/Channel/Channel.cpp\
		Classes/Server/Cmds/Private_msg/sendPrivateMsg.cpp\
		Classes/Server/Cmds/Nick/nick.cpp\
		Classes/Server/Cmds/Pass/passCmd.cpp\
		Classes/Server/Cmds/User/userCmd.cpp\
		Classes/Server/Cmds/Bot/botCmd.cpp\
		Classes/Server/Cmds/Kick/kick.cpp\
		Classes/Server/Cmds/Part/part.cpp\
		Classes/Server/Cmds/Mode/mode.cpp\
		Classes/Server/Cmds/Mode/o.cpp\
		Classes/Server/Cmds/Mode/k.cpp\
		Classes/Server/Cmds/Mode/l.cpp\
		Classes/Server/Cmds/Mode/t.cpp\
		Classes/Server/Cmds/Mode/i.cpp\
		Classes/Server/Cmds/Notice/sendNotice.cpp\
		Classes/Server/Cmds/Topic/topic.cpp\
		Classes/Server/Cmds/Invite/invite.cpp\
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
	rm -f BOT/Bot.o

fclean: clean
	rm -f $(NAME)
	rm -f $(BOTNAME)

re: fclean all

bot:
	g++ -Wall -Wextra -Werror -std=c++98 BOT/Bot.cpp -o $(BOTNAME)

.PHONY: all clean fclean re
