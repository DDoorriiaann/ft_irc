#ifndef Irc_HPP
#define Irc_HPP

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include "../Irc/Irc.hpp"
#include "../Server/Server.hpp"
#include "../Client/Client.hpp"


#define SUCCESS 1
#define FAILURE 0
#define	NEW_USER_MSG 			"\033[1;32m🎉[INFO]🎉\033[0m: New user on DG-Chat"
#define	MSG_SENT_SUCCESS	"\033[1;32m[INFO]\033[0m: Your message has been send.\n"

////// Utils Folder
int		checkPort(char *stringPort);
void	manaTcpServer(Server &server);

#endif 