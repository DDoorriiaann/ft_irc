#include "Client.hpp"

Client::Client(void) //Canonical
{
	return ;
}

Client::Client(std::string name)
{
	this->_username = name;
	this->_clientStatus = 0;
}

Client::Client(Client const & copy) //Canonical
{
    *this = copy;
}

Client::~Client() //Canonical
{
	return ;
}

Client & Client::operator=(Client const & rhs) //Canonical
{
    if (this != &rhs)
    {
		this->_username = rhs._username;
		this->_clientSocket = rhs._clientSocket;
		this->_clientStatus = rhs._clientStatus;
	}
    return *this;
}

//////////////// SET ////////////////

void	Client::setClientSocket(int socket)
{
	this->_clientSocket = socket;
	return ;
}

void	Client::setClientUsername(std::string username)
{
	this->_username = username;
	return ;
}

void	Client::setClientStatus(int status)
{
	this->_clientStatus = status;
	return ;
}

//////////////// GET ////////////////

std::string	Client::getClientUsername(void) const
{
	return (this->_username);
}


int		Client::getClientSocket(void) const
{
	return (this->_clientSocket);
}

int			Client::getClientStatus(void) const
{
	return (this->_clientStatus);
}