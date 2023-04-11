/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 23:11:57 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/09 23:11:58 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Server.hpp"

void	Server::_userCmd(std::istringstream& iss, Client& client, int clientSocket)
{
	std::string	message;
	std::string	username;
	int			clientStatus;

	getline(iss, username);
	clientStatus = client.getClientStatus();

	if (clientStatus == CONNECTED)
	{
		send(clientSocket, &USERNAME_ALREADY_SET, sizeof(USERNAME_ALREADY_SET), 0);
		return;
	}
	else if (username.empty())
	{
		send(clientSocket, &NO_USERNAME, sizeof(NO_USERNAME), 0);
		return;
	}
	username = username.substr(1);
	if (_checkNoWhiteSpace(username) == FAILURE)
	{
		send(clientSocket, &SPACE_IN_USERNAME, sizeof(SPACE_IN_USERNAME), 0);
		return;
	}
	else if (searchClient(username) != UNKNOWN)
	{
		send(clientSocket, &USERNAME_ALREADY_SET, sizeof(USERNAME_ALREADY_SET), 0);
		return;
	}

	client.setClientStatus(CONNECTED);
	client.setClientUsername(username);
	message += SUCCESS_CONNECTION;
	message += "[INFO]: Welcome " + username + " to DG-CHAT 🎉\n";
	send(clientSocket, message.c_str(), message.length(), 0);
	return;
}
