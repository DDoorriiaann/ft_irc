#include "Server.hpp"

Server::Server(void) //Canonical
{
	return;
}

Server::Server(Server const& copy) //Canonical
{
	*this = copy;
}

Server::~Server() //Canonical
{
	return;
}

Server& Server::operator=(Server const& rhs) //Canonical
{
	if (this != &rhs)
	{
		this->_socketServer = rhs._socketServer;
	}
	return *this;
}

//////////////// GET ////////////////

Client& Server::getClient(int index)
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

void	Server::setClient(Client& client)
{
	this->_client.push_back(client);
	this->_nbrClient++;
	return;
}

int    Server::searchClient(std::string userName)

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

void	Server::_unsetClient(Client& client)
{
	std::string	clientUsername;
	int	clientIndex;

	clientUsername = client.getClientUsername();
	clientIndex = searchClient(clientUsername);
	_client.erase(_client.begin() + clientIndex);
	return;
}

void	Server::_closeAllSocket(void)
{
	for (int i = 0; i < _nbrClient; i++)
		close(getClient(i).getClientSocket());
	if (_socketServer > 0)
		close(_socketServer);
	return;
}

////// CHECK /////////

int	Server::_checkHaveFullEntry(Client& client, char buf[], int ret)
{
	unsigned long found;

	buf[ret] = '\0';
	client.appendUserEntry(buf);
	found = std::string(buf).find("\n", 0);
	if (found != std::string::npos)
	{
		return (SUCCESS);
	}
	return (FAILURE);
}