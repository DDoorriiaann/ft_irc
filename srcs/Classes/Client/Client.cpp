#include "Client.hpp"

Client::Client(void) //Canonical
{
	return;
}

Client::Client(std::string name)
{
	this->_username = name;
	this->_nickName = "";
	this->_clientStatus = 0;
}

Client::Client(Client const& copy) //Canonical
{
	*this = copy;
}

Client::~Client() //Canonical
{
	return;
}

Client& Client::operator=(Client const& rhs) //Canonical
{
	if (this != &rhs)
	{
		this->_userEntry = rhs._userEntry;
		this->_username = rhs._username;
		this->_nickName = rhs._nickName;
		this->_clientSocket = rhs._clientSocket;
		this->_clientStatus = rhs._clientStatus;
	}
	return *this;
}

//////////////// SET ////////////////

void	Client::setClientSocket(int socket)
{
	this->_clientSocket = socket;
	return;
}

void	Client::setClientUsername(std::string username)
{
	this->_username = username;
	return;
}

void	Client::setClientStatus(int status)
{
	this->_clientStatus = status;
	return;
}

void	Client::setNickName(std::string nickName)
{
	this->_nickName = nickName;
	return;
}

//////////////// GET ////////////////

std::string	Client::getClientUsername(void) const
{
	return (this->_username);
}

std::string	Client::getClientNickName(void) const
{
	return (this->_nickName);
}


int		Client::getClientSocket(void) const
{
	return (this->_clientSocket);
}

int			Client::getClientStatus(void) const
{
	return (this->_clientStatus);
}

std::string	Client::getFullName(void) const
{
	std::string	FullName;

	FullName = this->_username;
	if (this->_nickName != "")
		FullName += " (" + this->_nickName + ")";
	std::cout << "FullName: " << FullName << std::endl; // !DEBUG
	return (FullName);
}

void	Client::appendUserEntry(std::string entry)
{
	_userEntry.append(entry);
	return;
}

std::string	Client::getUserEntry(void) const
{
	return (_userEntry);
}

void		Client::wipeUserEntry(void)
{
	_userEntry = "";
	return;
}