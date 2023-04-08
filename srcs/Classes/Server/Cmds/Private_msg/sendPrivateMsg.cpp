/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendPrivateMsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:10:45 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/05 13:10:46 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../Server.hpp"

#define	PRIVATE_CHAT_HEADER "[PRIVATE CHAT] "
#define ERROR_EMPTY_MSG "[ERROR]: Empty private chat.\n"
#define ERROR_UNKNOWN_CLIENT "[ERROR]: This user doesn't exit.\n"

void	sendAllMsgToClient(std::istringstream& iss, Client &client, int destSocket, int clientSocket);

int Server::_sendPrivateChat(std::istringstream& iss, Client& client, int clientSocket)
{
	std::string	destUserName;
	std::string	message;
	int			destClientIndex;
	int			destSocket;
	(void)client;

	iss >> destUserName;
	destClientIndex = searchClient(destUserName);
	if (destClientIndex == UNKNOWN)
	{
		send(clientSocket, &ERROR_UNKNOWN_CLIENT, sizeof(ERROR_UNKNOWN_CLIENT), 0);
		return (FAILURE);
	}

	destSocket = getClient(searchClient(destUserName)).getClientSocket();
	sendAllMsgToClient(iss, client, destSocket, clientSocket);

	return (SUCCESS);
}

void	sendAllMsgToClient(std::istringstream& iss, Client &client, int destSocket, int clientSocket)
{
	std::string	header;
	std::string message;

	getline(iss, message);
	if (message.empty())
	{
		send(clientSocket, ERROR_EMPTY_MSG, sizeof(ERROR_EMPTY_MSG), 0);
		return ;
	}
	//std::cout << "Sender's nickname : \n" << client.getClientNickName() << std::endl << std::endl;
	header += PRIVATE_CHAT_HEADER + client.getFullName() + ":" + message + "\n";
	
	send(destSocket, header.c_str(), header.length(), 0);
	send(clientSocket, MSG_SENT_SUCCESS, sizeof(MSG_SENT_SUCCESS), 0);
	return ;
} 	