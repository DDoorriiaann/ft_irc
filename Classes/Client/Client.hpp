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

		int			getClientSocket(void) const;
		int			getClientStatus(void) const;
		std::string	getClientUsername(void) const;

		void		setClientSocket(int socket);
		void		setClientUsername(std::string username);
		void		setClientStatus(int status);

	private:


		std::string	_username;
		int			_clientSocket;
		int			_clientStatus; // 0 -> he is entering the password, 2 -> he is choosing is Username, 3 -> he is connected !
};

#endif 