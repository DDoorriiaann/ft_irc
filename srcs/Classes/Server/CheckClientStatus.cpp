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

#define BAD_PASSWORD 			"Bad password.\n"
#define USERNAME_ALREADY_SET 	"[ERROR] Username already set.\n"
#define	DISCONNECT				"[INFO] DISCONNECT.\n"

int	Server::_checkClientStatus(Client& client, std::string clientEntry, int clientSocket, int clientStatus)
{
	std::istringstream	stream(clientEntry);
	std::string			header;
	std::string 		password;
	std::string			nickName;
	std::string			username;

	if (clientStatus == CONNECTED)
		return (CONTINUE);

	getline(stream, header);
	header = header.substr(0, header.length() - 1);

	if (header == HEADER_HXCHAT)
	{
		getline(stream, password);
		getline(stream, nickName);
		getline(stream, username);

		if (password.length() < 5)
			return (CONTINUE);

		password = password.substr(5, password.length() - 6);

		if (_isPwd_hexchat(password) == SUCCESS)
		{
			std::istringstream	usernameStream(username);
			std::string			parsedUsername;

			usernameStream >> parsedUsername;
			usernameStream >> parsedUsername;
			if (searchClient(parsedUsername) != -1)
			{
				send(clientSocket, &USERNAME_ALREADY_SET, sizeof(USERNAME_ALREADY_SET), 0);
				send(clientSocket, &DISCONNECT, sizeof(DISCONNECT), 0);
				close(clientSocket);
				_unsetClient(client);
				_nbrClient--;
				return (STOP);
			}
			client.setClientUsername(parsedUsername);
			client.setClientStatus(CONNECTED);
			return (STOP);
		}
		else
		{
			send(clientSocket, &BAD_PASSWORD, sizeof(BAD_PASSWORD), 0);
			close(clientSocket);
			_unsetClient(client);
			_nbrClient--;
			return (STOP);
		}
	}

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
	std::cout << "Client Entry: \"" << clientEntry.length() << "\" mdp: \"" << _serverPwd.length() << "\"" << std::endl;
	if (clientEntry == _serverPwd)
		return (SUCCESS);
	std::cout << "NON" << std::endl;
	return (FAILURE);
}

