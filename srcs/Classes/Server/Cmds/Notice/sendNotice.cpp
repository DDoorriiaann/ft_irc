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

#define	PRIVATE_CHAT_HEADER "[NOTICE] from "

int Server::_sendNotice(std::istringstream& iss, Client& client, int clientSocket)
{
	std::string	destUserName;
	std::string	message;
	int			destClientIndex;
	int			destSocket;

	iss >> destUserName;
	destClientIndex = searchClient(destUserName);
	if (destClientIndex == UNKNOWN)
		return (FAILURE);

	destSocket = getClient(searchClient(destUserName)).getClientSocket();
	_sendAllNoticeClient(iss, client, destSocket, clientSocket, destUserName);

	return (SUCCESS);
}

void	Server::_sendAllNoticeClient(std::istringstream& iss, Client& client, int destSocket, int clientSocket, std::string destUserName)
{
	Client		destClient;
	std::string	message;
	std::string content;

	destClient = _client[searchClient(destUserName)];
	getline(iss, content);

	if (content.empty())
		return;

	if (clientSocket != destSocket)
	{
		message = PRIVATE_CHAT_HEADER + client.getFullName() + " to you :" + content + "\n";
		send(destSocket, message.c_str(), message.length(), 0);
	}
	else
	{
		message = (std::string)PRIVATE_CHAT_HEADER + "you to yourself :" + content + "\n";
		send(clientSocket, message.c_str(), message.length(), 0);
	}
	return;
}