/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkClientStatus.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:53:57 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/04 22:53:58 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Server.hpp"

int	Server::_checkClientStatus(Client& client, std::string clientEntry, int clientSocket, int clientStatus)
{
	if (clientStatus == PWD_ENTRY_STATUS && _isPwd(clientEntry) == FAILURE)
	{
		send(clientSocket, &MSG_WRONG_PWD, sizeof(MSG_WRONG_PWD), 0);
		return (STOP);
	}
	else if (clientStatus == PWD_ENTRY_STATUS)
	{
		send(clientSocket, &MSG_ENTER_USRNM, sizeof(MSG_ENTER_USRNM), 0);
		client.setClientStatus(USERNAME_ENTRY_STATUS);
		return (STOP);
	}
	else
	{
		if (clientEntry.empty())
		{
			send(clientSocket, &EMPTY_USERNAME, sizeof(EMPTY_USERNAME), 0);
			send(clientSocket, &MSG_ENTER_USRNM, sizeof(MSG_ENTER_USRNM), 0);
			return (STOP);
		}
		if (_checkNoWhiteSpace(clientEntry) == FAILURE)
		{
			send(clientSocket, &SPACE_IN_USERNAME, sizeof(SPACE_IN_USERNAME), 0);
			send(clientSocket, &MSG_ENTER_USRNM, sizeof(MSG_ENTER_USRNM), 0);
			return (STOP);
		}
		if (searchClient(clientEntry) != -1)
		{
			send(clientSocket, &USERNAME_ALREADY_SET, sizeof(USERNAME_ALREADY_SET), 0);
			send(clientSocket, &MSG_ENTER_USRNM, sizeof(MSG_ENTER_USRNM), 0);
			return (STOP);
		}
		client.setClientUsername(clientEntry);
		client.setClientStatus(CONNECTED);
		send(clientSocket, &WELCOME, sizeof(WELCOME), 0);
		return (STOP);
	}
}

int	Server::_isPwd_hexchat(std::string clientEntry)
{
	std::istringstream connectionHeader(clientEntry);
	std::string 		line;

	if (clientEntry == _serverPwd)
		return (SUCCESS);

	getline(connectionHeader, line);
	getline(connectionHeader, line);
	line = line.substr(5, line.length() - 6);

	if (line.compare(_serverPwd) == 0)
		return (SUCCESS);

	return (FAILURE);
}

int	Server::_isPwd(std::string clientEntry)
{
	if (clientEntry == _serverPwd)
		return (SUCCESS);
	return (FAILURE);
}

