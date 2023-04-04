#ifndef Client_HPP
#define Client_HPP

#include <iomanip>
#include <iostream> 
#include <string>
#include <stdlib.h>

class Client
{
	public:
   		Client(void); //Canonical
    	Client(Client const & copy); //Canonical
    	~Client(); //Canonical
		Client(std::string name);

    	Client	&operator=(Client const & rhs); //Canonical

		int			getClientSocket(void);
		std::string	getClientUsername(void);

		void		setClientSocket(int socket);
		void		setClientUsername(std::string username);

	private:


		std::string	_username;
		int			_clientSocket;
		bool		_isRegistered;
};

#endif 