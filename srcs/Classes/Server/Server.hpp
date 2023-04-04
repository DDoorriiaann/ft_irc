#ifndef Server_HPP
#define Server_HPP

#include "../Client/Client.hpp"
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>

#define SUCCESS 1
#define	FAILURE 0
#define	MSG_CREATION_SUCCESS	"\033[1;32m[INFO]\033[0m: The server as been created succesfully ✅"
#define	MSG_CONNECTED			"\033[1;32mCONNECTED ✅\n\033[0m"

class Client;
class Server
{
	public:

   		Server(void); //Canonical
		Server(unsigned short port);
    	Server(Server const & copy); //Canonical
    	~Server(); //Canonical

    	Server	&operator=(Server const & rhs); //Canonical
		int		getServerSocket(void);
		int		getNbrClient(void);
		Client	getClient(int index);
		void	setClient(Client &client);

	private:

		int					_socketServer;
		std::vector<Client>	_client;
		int					_nbrClient;
};

#endif 