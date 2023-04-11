/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botCmd.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:51:59 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/10 01:52:00 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Server.hpp"

#define WRONG_REQUEST "[ERROR]: unknown command\n"

void	Server::_botCmd(std::istringstream& iss, Client& client, int clientSocket)
{
	std::string	mode;
	std::string	message;

	getline(iss, mode);
	if (mode.empty())
	{
		send(clientSocket, &WRONG_REQUEST, sizeof(WRONG_REQUEST), 0);
		return ;
	}
	mode = mode.substr(1);
	if (mode == "register")
	{
		if (_clientBotList.count(client.getClientUsername()) == 0)
			_clientBotList[client.getClientUsername()] = clientSocket;
	}
	else if (mode == "unregister")
	{
		if (_clientBotList.count(client.getClientUsername()) == 1)
			_clientBotList.erase(client.getClientUsername());
	}
	else
		send(clientSocket, &WRONG_REQUEST, sizeof(WRONG_REQUEST), 0);
	return;
}
