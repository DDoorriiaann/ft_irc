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
#define ERROR_UNKNOWN_CLIENT "[ERROR]: This user doesn't exit.\n"

void	sendAllMsgToClient(std::istringstream& iss, int destSocket);

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
	message += PRIVATE_CHAT_HEADER + client.getClientUsername() + ": ";
	
	send(destSocket, &message, message.length(), 0);
	sendAllMsgToClient(iss, destSocket);
	send(clientSocket, MSG_SENT_SUCCESS, sizeof(MSG_SENT_SUCCESS), 0);

	return (SUCCESS);
}

void	sendAllMsgToClient(std::istringstream& iss, int destSocket)
{
	std::string message;

	getline(iss, message);
	send(destSocket, "\n> ", sizeof("\n> "), 0);
	send(destSocket, message.c_str(), message.length(), 0);
}