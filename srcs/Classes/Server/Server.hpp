#ifndef Server_HPP
#define Server_HPP

#include "../Client/Client.hpp"
#include "../Channel/Channel.hpp"
#include "defines.hpp"
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <map>
#include <sstream>

class Client;
class Server
{
public:

	Server(void); //Canonical
	Server(Server const& copy); //Canonical
	~Server(); //Canonical

	Server& operator=(Server const& rhs); //Canonical

	void	run(void);
	int		init(int port, std::string pwd);

	int		getServerSocket(void) const;
	int		getNbrClient(void) const;
	Client& getClient(int index);
	void	setClient(Client& client);
	int		searchClient(std::string userName);


	//CHANNELS

	bool 	createChannel(const std::string& name);
	bool 	joinChannel(const std::string& channelName, const std::string& user);
	bool 	leaveChannel(const std::string& channelName, const std::string& user);
	bool 	isValidChannel(const std::string& channelName) const;
	Channel* getChannel(const std::string& channelName);
	void 	sendMessageToChannel(const std::string& channelName, const std::string& username, const std::string& fullName, const std::string& message);
	const std::string getChannelListAsString(void) const;
	const std::map<std::string, Channel>& getChannels() const;

private:

	void	_addUser(sockaddr_in& addrClient);
	int		_resetFd(fd_set& read_fd_set);
	void	_handelChatEntry(Client& client, int clientSocket);
	void	_handleCmd(std::istringstream& iss, std::string& command, Client& client, int clientSocket);
	void	_checkNewEntries(fd_set read_fd_set);
	int		_checkClientStatus(Client& client, std::string clientEntry, int clientSocket, int clientStatus);
	int		_isPwd(std::string clientEntry);
	int		_isPwd_hexchat(std::string clientEntry);
	int 	_sendPrivateChat(std::istringstream& iss, Client& client, int clientSocket);
	void	_bot(std::istringstream& iss, int clientSocket);
	void	_nick(std::istringstream& iss, Client& client, int clientSocket);
	void	_kick(std::istringstream& iss, Client& client, int clientSocket);
	void	_mode(std::istringstream& iss, Client& client, int clientSocket);
	void	_kickAllUsersFromChannel(Channel& channel);
	void	_part(std::istringstream& iss, Client& client, int clientSocket);
	void	_joinCmd(std::istringstream& iss, Client client, int clientSocket);
	void	_handelSimpleChat(Client client, std::string userEntry, int clientSocket);
	void	_unsetClient(Client& client);
	void	_closeAllSocket(void);
	int		_checkHaveFullEntry(Client& client, char buf[1024], int ret);
	int		_checkNoWhiteSpace(std::string str);
	void	_sendAllMsgToClient(std::istringstream& iss, Client& client, int destSocket, int clientSocket, std::string destUserName);
	void	_passCmd(std::istringstream& iss, Client& client, int clientSocket);
	void	_userCmd(std::istringstream& iss, Client& client, int clientSocket);
	void	_botCmd(std::istringstream& iss, Client& client, int clientSocket);
	void	_sendTimeToAllClient(std::string message);

	std::string			_serverPwd;
	int					_socketServer;
	int					_nbrClient;
	std::vector<Client>	_client;
	std::map<std::string, Channel> _channels;
	std::map<std::string, int>	_clientBotList; // #BOT
	bool						_botIsSet;
};

#endif 