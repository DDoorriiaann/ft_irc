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

//////////////// GET ////////////////

Client	&Server::getClient(int index)
{
	return (this->_client[index]);
}

int		Server::getServerSocket(void) const
{
	return (this->_socketServer);
}

int		Server::getNbrClient(void) const
{
	return (this->_nbrClient);
}

//////////////// SET ////////////////

void	Server::setClient(Client &client)
{
	this->_client.push_back(client);
	this->_nbrClient++;
	return ;
}

//////////////// Function //////////////
int	Server::searchClient(std::string userName)
{
	int index;

	index = 0;
	while (index < _nbrClient)
	{
		if (_client[index].getClientUsername() == userName)
			return (index);
		index++;
	}
	return (-1);
}