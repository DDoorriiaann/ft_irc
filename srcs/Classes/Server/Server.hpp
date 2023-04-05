#ifndef Server_HPP
#define Server_HPP

#include "../Client/Client.hpp"
#include "../Channel/Channel.hpp"
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
#include <map>
#include <sstream>

#define CONTINUE 1
#define	STOP 0
#define SUCCESS 1
#define	FAILURE 0

#define	PWD_ENTRY_STATUS		0
#define USERNAME_ENTRY_STATUS	1
#define	CONNECTED				2

#define	MSG_CREATION_SUCCESS			"\033[1;32m[INFO]\033[0m: The server as been created succesfully ✅"
#define	MSG_CONNECTED					"\033[1;32m[INFO]\033[0m: Please enter the password.\nPassword: "
#define	NEW_USER_MSG 					"\033[1;32m[INFO]\033[0m: New user on DG-Chat 🎉"
#define	MSG_SENT_SUCCESS				"\033[1;32m[INFO]\033[0m: Your message has been send.\n"
#define	MSG_WRONG_PWD					"\033[1;31m[ERROR]\033[0m: Wrong Password.\nPassword: "
#define	MSG_ENTER_USRNM					"\033[1;32m[INFO]\033[0m: Enter an username: "
#define	WELCOME							"\033[1;32mCONNECTED ✅\n[INFO]\033[0m: Welcome "

class Client;
class Server
{
public:

	Server(void); //Canonical
	Server(Server const& copy); //Canonical
	~Server(); //Canonical

	Server& operator=(Server const& rhs); //Canonical

	void	run(void);
	void	init(int port, std::string pwd);

	int		getServerSocket(void) const;
	int		getNbrClient(void) const;
	Client& getClient(int index);
	void	setClient(Client& client);
	int		searchClient(std::string userName);

	//CHANNELS

	bool createChannel(const std::string& name);
	bool joinChannel(const std::string& channelName, const std::string& user);
	bool leaveChannel(const std::string& channelName, const std::string& user);
	const std::map<std::string, Channel>& getChannels() const;
	void 	sendMessageToChannel(const std::string& channelName, const std::string& username, const std::string& message);

private:

	void	_addUser(sockaddr_in& addrClient);
	int		_resetFd(fd_set& read_fd_set);
	void	_handelChatEntry(Client& client, int clientSocket);
	void	_checkNewEntries(fd_set read_fd_set);
	int		_checkClientStatus(Client& client, std::string clientEntry, int clientSocket, int clientStatus);
	int		_isPwd(std::string clientEntry);

	std::string			_serverPwd;
	int					_socketServer;
	int					_nbrClient;
	std::vector<Client>	_client;
	std::map<std::string, Channel> _channels;
};

#endif 