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

void	Server::run(void)
{
	struct		sockaddr_in	addrClient;
	fd_set					read_fd_set;
	int						lastFd;

	while (1)
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
	}
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
	Client		client("unknown");
	socklen_t	csize = sizeof(int);
	int			socketClient;

	socketClient = accept(_socketServer, (struct sockaddr*)&addrClient, &csize);
	client.setClientSocket(socketClient);

	this->setClient(client);

	send(client.getClientSocket(), &MSG_CONNECTED, sizeof(MSG_CONNECTED), 0);
	std::cout << NEW_USER_MSG << std::endl;
	return;
}

void	Server::_checkNewEntries(fd_set read_fd_set)
{
	for (int i = 0; i < _nbrClient; i++)
		if (FD_ISSET(this->getClient(i).getClientSocket(), &read_fd_set))
			_handelChatEntry(this->getClient(i), this->getClient(i).getClientSocket());
	return;
}

void	Server::_handelChatEntry(Client& client, int clientSocket)
{
	int		ret;
	char	buf[1024];

	ret = recv(clientSocket, &buf, sizeof(buf), 0);
	buf[ret - 1] = '\0';

	if (_checkClientStatus(client, buf, clientSocket, client.getClientStatus()) == STOP)
		return;
	// Vérifier si le message commence par un slash (/)
	if (buf[0] == '/') {
		// Extraire la commande et les arguments du message
		std::string message(buf + 1);
		std::istringstream iss(message);
		std::string command;
		iss >> command;

		if (command == "join") {
			std::string channelName;
			iss >> channelName;

			if (!channelName.empty()) {
				// Traiter la commande /join
				joinChannel(channelName, client.getClientUsername());
			}
			else {
				// Gérer l'erreur (par exemple, envoyer un message d'erreur à l'utilisateur)
			}
		}
		else {
			// Gérer d'autres commandes ou les commandes inconnues
		}
	}
	else {
		// Traiter le message en tant que message de chat normal
		if (buf[0] != '/') {
			std::string message(buf);
			std::istringstream iss(message);
			std::string channelIndicator;
			iss >> channelIndicator;

			if (channelIndicator.size() > 1 && channelIndicator[0] == '#') {
				// Le message est destiné à une channel spécifique
				std::string channelName = channelIndicator.substr(1);
				std::string messageToSend;
				std::getline(iss, messageToSend);

				// Envoyer le message à la channel spécifique
				sendMessageToChannel(channelName, client.getClientUsername(), messageToSend);
			}
			else {
				// Traiter le message comme un message normal sans channel spécifique
				send(clientSocket, &MSG_SENT_SUCCESS, sizeof(MSG_SENT_SUCCESS), 0);
				send(clientSocket, &"\033[1;0m> \033[0m", sizeof("\033[1;0m> \033[0m"), 0);
				std::cout << client.getClientUsername() << ": " << buf << std::endl;
			}
		}
	}
}