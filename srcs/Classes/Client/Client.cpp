#include "Client.hpp"

Client::Client(void) //Canonical
{
	return ;
}

Client::Client(std::string name)
{
	this->_username = name;
	
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

//////////////// GET ////////////////

std::string	Client::getClientUsername(void)
{
	return (this->_username);
}


int		Client::getClientSocket(void)
{
	return (this->_clientSocket);
}