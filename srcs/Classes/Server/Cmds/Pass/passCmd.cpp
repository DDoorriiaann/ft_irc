/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:24:40 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/09 22:24:41 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../Server.hpp"

void	Server::_passCmd(std::istringstream& iss, Client& client, int clientSocket)
{
	std::string	passWord;
	int			clientStatus;

	getline(iss, passWord);
	passWord = passWord.substr(1);
	clientStatus = client.getClientStatus();

	if (passWord.empty() || passWord != _serverPwd)
	{
		send(clientSocket, &BAD_PASSWORD, sizeof(BAD_PASSWORD), 0);
		return;
	}

	if (clientStatus != PWD_ENTRY_STATUS)
	{
		send(clientSocket, &PWD_ALREADY_PAST, sizeof(PWD_ALREADY_PAST), 0);
		if (clientStatus == USERNAME_ENTRY_STATUS)
			send(clientSocket, &USE_USER_CMD, sizeof(USE_USER_CMD), 0);
		return;
	}

	send(clientSocket, &MSG_ENTER_USRNM, sizeof(MSG_ENTER_USRNM), 0);
	client.setClientStatus(USERNAME_ENTRY_STATUS);
	return;
}