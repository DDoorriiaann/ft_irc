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

int	Server::_checkClientStatus(Client &client, std::string clientEntry, int clientSocket, int clientStatus)
{
	if (clientStatus == CONNECTED)
		return (CONTINUE);
	if (clientStatus == PWD_ENTRY_STATUS && _isPwd(clientEntry) == FAILURE)
	{
		send(clientSocket, &MSG_WRONG_PWD, sizeof(MSG_WRONG_PWD), 0);
		return (STOP);
	}
	else if (clientStatus == 0)
	{
		send(clientSocket, &MSG_ENTER_USRNM, sizeof(MSG_ENTER_USRNM), 0);
		client.setClientStatus(USERNAME_ENTRY_STATUS);
		return (STOP);
	}
	else
	{
		client.setClientUsername(clientEntry);
		client.setClientStatus(CONNECTED);
		send(clientSocket, &WELCOME, sizeof(WELCOME), 0);
		send(clientSocket, client.getClientUsername().c_str(), sizeof(client.getClientUsername().c_str()), 0);
		send(clientSocket, &" \n", sizeof(" \n"), 0);
		send(clientSocket, &"\033[1;0m> \033[0m", sizeof("\033[1;0m> \033[0m"), 0);
		return (STOP);
	}
}

int	Server::_isPwd(std::string clientEntry)
{
	if (clientEntry == _serverPwd)
		return (SUCCESS);
	return (FAILURE);
}
