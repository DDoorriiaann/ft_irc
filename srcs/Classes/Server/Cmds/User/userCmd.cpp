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

#define	UNKNOWN					-1
#define	NO_USERNAME				"[ERROR]: No username.\n[INFO]: Use /cmd USER <username> to finish the connection.\n"
#define	USERNAME_ALREADY_SET	"[ERROR]: Username already set.\n"
#define	SPACE_IN_USERNAME		"[ERROR]: In the username the spaces are forbidden.\n"
#define	USERNAME_ALREADY_SET	"[ERROR]: Username already set.\n"
#define	SUCCESS_CONNECTION		"[INFO]: You are now connected ✅\n"

void	Server::_userCmd(std::istringstream& iss, Client& client, int clientSocket)
{
	std::string	message;
	std::string	username;
	int			clientStatus;

	getline(iss, username);
	username = username.substr(1);
	clientStatus = client.getClientStatus();

	if (clientStatus == CONNECTED)
	{
		send(clientSocket, &USERNAME_ALREADY_SET, sizeof(USERNAME_ALREADY_SET), 0);
		return ;
	}
	else if (username.empty())
	{
		send(clientSocket, &NO_USERNAME, sizeof(NO_USERNAME), 0);
		return ;
	}
	else if (_checkNoWhiteSpace(username) == FAILURE)
	{
		send(clientSocket, &SPACE_IN_USERNAME, sizeof(SPACE_IN_USERNAME), 0);
		return ;
	}
	else if (searchClient(username) != UNKNOWN)
	{
		send(clientSocket, &USERNAME_ALREADY_SET, sizeof(USERNAME_ALREADY_SET), 0);
		return ;
	}

	client.setClientStatus(CONNECTED);
	client.setClientUsername(username);
	message += SUCCESS_CONNECTION;
	message += "[INFO]: Welcome " + username + " to DG-CHAT 🎉\n"; 
	send(clientSocket, message.c_str(), message.length(), 0);
	return ;
}
