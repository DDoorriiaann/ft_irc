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

#define UNKNOWN -1
#define	PRIVATE_CHAT_HEADER "\033[1;31m[PRIVATE CHAT]\033[0m "
#define ERROR_UNKNOWN_CLIENT "\033[1;31m[ERROR]\033[0m: This user doesn't exit."
/*
Server::_sendPrivateChat(Client	&client, char *clientEntry)
{
	std::istringstream iss(clientEntry);
	std::string userName;
	return (SUCCESS);
}
*/
/*int	Server::_sendPrivateChat(std::string srcUserName, std::string destUserName, std::string clientMsg, int clientSocket)
{
	int destSocket;

	destSocket = searchClient(destUserName);
	if (destSocket == UNKNOWN)
	{
		send(clientSocket, &ERROR_UNKNOWN_CLIENT, sizeof(ERROR_UNKNOWN_CLIENT), 0);
		return (FAILURE);
	}
	send(destSocket, PRIVATE_CHAT_HEADER, sizeof(PRIVATE_CHAT_HEADER), 0);
	send(destSocket, srcUserName.c_str(), sizeof(srcUserName.c_str()), 0);
	send(destSocket, clientMsg.c_str(), sizeof(clientMsg.c_str()), 0);
	return (SUCCESS);
}*/