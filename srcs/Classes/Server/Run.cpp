/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Run.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:14:08 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/04 19:14:09 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Server.hpp"
#include <signal.h>

bool	QUIT_SERVER = false;

void	catchSignal(int sig)
{
	if (sig == SIGINT)
	{
		QUIT_SERVER = true;
		return;
	}
	return;
}

void	Server::run(void)
{
	struct		sockaddr_in	addrClient;
	fd_set					read_fd_set;
	int						lastFd;

	signal(SIGINT, catchSignal);
	while (QUIT_SERVER == false)
	{
		lastFd = _resetFd(read_fd_set);
		if (select(lastFd + 1, &read_fd_set, NULL, NULL, NULL) > 0)
		{
			// Check the server
			if (FD_ISSET(_socketServer, &read_fd_set))
				_addUser(addrClient);
			// Check All client if one are post something
			_checkNewEntries(read_fd_set);
		}
		if (searchClient("PasEncore13h13Bot") != -1)
			_botIsSet = 1;
		else
			_botIsSet = 0;
	}
	std::cout << "\n Server shutdown." << std::endl;
	_closeAllSocket();
	return;
}

int	Server::_resetFd(fd_set& read_fd_set)
{
	FD_ZERO(&read_fd_set);
	FD_SET(_socketServer, &read_fd_set);

	for (int i = 0; i < _nbrClient; i++)
		FD_SET(this->getClient(i).getClientSocket(), &read_fd_set);

	if (_nbrClient == 0) // this return use when we have just a server socket.
		return (_socketServer);
	return (this->getClient(_nbrClient - 1).getClientSocket()); // this return is for keep the last FD_SET use in select() func
}

void	Server::_addUser(sockaddr_in& addrClient)
{
	Client		client("");
	socklen_t	csize = sizeof(int);
	int			socketClient;

	socketClient = accept(_socketServer, (struct sockaddr*)&addrClient, &csize);
	client.setClientSocket(socketClient);
	this->setClient(client);
	std::cout << NEW_USER_MSG << std::endl;
	return;
}

void	Server::_checkNewEntries(fd_set read_fd_set)
{
	for (int i = 0; i < _nbrClient; i++)
	{
		if (FD_ISSET(this->getClient(i).getClientSocket(), &read_fd_set))
			_handelChatEntry(this->getClient(i), this->getClient(i).getClientSocket());
	}
	return;
}

///////////////////////////////////
///////////////	HANDLE CHAT ENTRY
//////////////////////////////////

std::string	deleteBufferedWriter(std::string string)
{
	unsigned long found;

	found = string.find("\r", 0);
	if (found != std::string::npos)
		string = string.substr(0, string.length() - 1);
	return (string);
}

void	Server::_handelChatEntry(Client& client, int clientSocket)
{
	std::string userEntry;
	std::string header;
	std::string command;
	int			ret;
	char		buf[1024];

	memset(buf, 0, sizeof(buf));
	ret = recv(clientSocket, &buf, sizeof(buf), 0);
	if (ret == 0)
	{
		close(clientSocket);
		_unsetClient(client);
		_nbrClient--;
		return;
	}
	if (_checkHaveFullEntry(client, buf, ret) == FAILURE)
		return;

	userEntry = client.getUserEntry();
	userEntry = userEntry.substr(0, userEntry.length() - 1);
	userEntry = deleteBufferedWriter(userEntry);
	client.wipeUserEntry();

	std::string 		message(userEntry);
	std::istringstream	iss(message);

	if (client.getClientUsername() == "PasEncore13h13Bot")
		_sendTimeToAllClient(userEntry);
	iss >> header;
	if (header.compare(QUIT_COMMAND_HEXCHAT) == 0)
	{
		close(clientSocket);
		_unsetClient(client);
		_nbrClient--;
		return;
	}

	if (header.compare("cmd") != 0 && header.compare("/cmd") != 0)
	{
		send(clientSocket, &CMD_NOT_FOUND, sizeof(CMD_NOT_FOUND), 0);
		return;
	}

	iss >> command;

	// Vérifier si le message commence par un slash (/)
	if (command[0] != '#')
		_handleCmd(iss, command, client, clientSocket);
	else
	{
		// Traite les commandes donnees par le client
		_handelSimpleChat(client, userEntry, clientSocket);
	}
	return;
}

///////////////////////////////////
///////////////	HANDLE CMD 
//////////////////////////////////

void	Server::_handleCmd(std::istringstream& iss, std::string& command, Client& client, int clientSocket)
{
	// Extraire la commande et les arguments du message
	if (command == PASS_COMMAND)
	{
		_passCmd(iss, client, clientSocket);
		return;
	}

	if (client.getClientStatus() == PWD_ENTRY_STATUS)
	{
		send(clientSocket, &ENTER_PWD_FIRST, sizeof(ENTER_PWD_FIRST), 0);
		return;
	}
	else if (command == USER_COMMAND)
	{
		_userCmd(iss, client, clientSocket);
		return;
	}

	if (client.getClientStatus() != CONNECTED)
		send(clientSocket, &ACCESS_DENIED, sizeof(ACCESS_DENIED), 0);
	else if (command == BOT_COMMAND)
		_botCmd(iss, client, clientSocket);
	else if (command == JOIN_COMMAND)
		_joinCmd(iss, client, clientSocket);
	else if (command == MSG_COMMAND)
		_sendPrivateChat(iss, client, clientSocket);
	else if (command == NICK_COMMAND)
		_nick(iss, client, clientSocket);
	else if (command == KICK_COMMAND)
		_kick(iss, client, clientSocket);
	else if (command == PART_COMMAND)
		_part(iss, client, clientSocket);
	else if (command == MODE_COMMAND)
		_mode(iss, client, clientSocket);
	else if (command == NOTICE_COMMAND)
		_sendNotice(iss, client, clientSocket);
	else if (command == TOPIC_COMMAND)
		_topic(iss, client, clientSocket);
	else
		send(clientSocket, &CMD_NOT_FOUND, sizeof(CMD_NOT_FOUND), 0);
	return;
}

void	Server::_joinCmd(std::istringstream& iss, Client client, int clientSocket)
{
	std::string channelName;

	iss >> channelName;
	if (channelName[0] != '#')
	{
		send(clientSocket, &CHANNEL_REQUIRES_HASHTAG, sizeof(CHANNEL_REQUIRES_HASHTAG), 0);
		return;
	}
	channelName = channelName.substr(1); // Delete the #.
	if (!channelName.empty())
	{
		std::string channelKey;
		std::string firstPart;
		std::string secondPart;

		iss >> firstPart;
		getline(iss, secondPart);
		channelKey = firstPart + secondPart;
		joinChannel(channelName, channelKey, client.getClientUsername());
	}

	else
	{
		// ERROR MESSAGE: Channel not found.
		send(clientSocket, &CHANNEL_NOT_FOUND, sizeof(CHANNEL_NOT_FOUND), 0);
	}
	return;
}

///////////////////////////////////
///////////////	HANDLE SIMPLE CHAT
//////////////////////////////////

void	Server::_handelSimpleChat(Client client, std::string userEntry, int clientSocket)
{
	std::string 		message(userEntry);
	std::string			channelIndicator;
	std::istringstream	iss(message);

	iss >> channelIndicator;
	iss >> channelIndicator;

	if (channelIndicator.size() > 1 && channelIndicator[0] == '#')
	{
		// Le message est destiné à une channel spécifique
		std::string channelName = channelIndicator.substr(1);
		std::string messageToSend;
		std::getline(iss, messageToSend);

		// Envoyer le message à la channel spécifique
		sendMessageToChannel(channelName, client.getClientUsername(), client.getFullName(), messageToSend);
	}
	else
	{
		std::string channelList = getChannelListAsString();
		std::string message = CHANNEL_LIST + (channelList.empty() ? "No active channels at this time" : channelList) + "\n";
		send(clientSocket, message.c_str(), message.length(), 0);
	}
	return;
}

void	Server::_sendTimeToAllClient(std::string message)
{
	std::map<std::string, int>::iterator itbeg = _clientBotList.begin();
	message += "\n";
	while (itbeg != _clientBotList.end())
	{
		send(itbeg->second, message.c_str(), message.length(), 0);
		itbeg++;
	}
	return;
}
