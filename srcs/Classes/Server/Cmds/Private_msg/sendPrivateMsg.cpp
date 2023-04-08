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

#define	PRIVATE_CHAT_HEADER "[PRIVATE CHAT] from "
#define ERROR_EMPTY_MSG "[ERROR]: Empty private chat.\n"
#define ERROR_UNKNOWN_CLIENT "[ERROR]: This user doesn't exit.\n"

void	sendAllMsgToClient(std::istringstream& iss, Client& client, int destSocket, int clientSocket, std::string destUserName);

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
	sendAllMsgToClient(iss, client, destSocket, clientSocket, destUserName);

	return (SUCCESS);
}

void	sendAllMsgToClient(std::istringstream& iss, Client& client, int destSocket, int clientSocket, std::string destUserName)
{
	std::string	message;
	std::string content;

	getline(iss, content);
	if (content.empty())
	{
		send(clientSocket, ERROR_EMPTY_MSG, sizeof(ERROR_EMPTY_MSG), 0);
		return;
	}
	message = PRIVATE_CHAT_HEADER + client.getFullName() + " to " + destUserName + " :" + content + "\n";

	if (clientSocket != destSocket)
	{
		message = PRIVATE_CHAT_HEADER + client.getFullName() + " to you :" + content + "\n";
		send(destSocket, message.c_str(), message.length(), 0);
		message = (std::string)PRIVATE_CHAT_HEADER + "you to " + destUserName + " :" + content + "\n";
		send(clientSocket, message.c_str(), message.length(), 0);
	}
	else
	{
		message = (std::string)PRIVATE_CHAT_HEADER + "you to yourself :" + content + "\n";
		send(clientSocket, message.c_str(), message.length(), 0);
	}
	return;
}