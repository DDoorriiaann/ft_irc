#include "Server.hpp"

Server::Server(void) //Canonical
{
	std::cout << "Server Constructeur called." << std::endl;
	return ;
}

Server::Server(Server const & copy) //Canonical
{
    std::cout << "Server Constructeur called." << std::endl;
    *this = copy;
}

Server::~Server() //Canonical
{
	std::cout << "Server Destructeur called." << std::endl;
	return ;
}

Server & Server::operator=(Server const & rhs) //Canonical
{
    if (this != &rhs)
    {
		this->_socketServer = rhs._socketServer;
	}
    return *this;
}

Server::Server(unsigned short port)
{
	struct	sockaddr_in	addrServer;

	this->_socketServer = socket(AF_INET, SOCK_STREAM, 0);
	this->_nbrClient = 0;

	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);

	bind(this->_socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer));
	listen(this->_socketServer, 10);

	std::cout << MSG_CREATION_SUCCESS << std::endl;
	return ;
}

Client	Server::getClient(int index)
{
	return (this->_client[index]);
}

int		Server::getServerSocket(void)
{
	return (this->_socketServer);
}

int		Server::getNbrClient(void)
{
	return (this->_nbrClient);
}

void	Server::setClient(Client &client)
{
	this->_client.push_back(client);
	this->_nbrClient++;
	return ;
}