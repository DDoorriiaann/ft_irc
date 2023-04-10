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
#define	IS_START		"[INFO]: The Bot \"PasEncore13h13Bot\" is now available.\n"
#define	IS_STOP		"[INFO]: The Bot \"PasEncore13h13Bot\" is now unavailable.\n"
#define	ALREADY_START "[ERROR]: The Bot \"PasEncore13h13Bot\" is already START.\n"
#define	ALREADY_STOP "[ERROR]: The Bot \"PasEncore13h13Bot\" is already STOP.\n"

void	Server::_botCmd(std::istringstream& iss, Client& client, int clientSocket)
{
	std::string	mode;
	std::string	message;

	getline(iss, mode);
	mode = mode.substr(1);
	if (mode == "start")
	{
		if (_clientBotList.count(client.getClientUsername()) == 0)
		{
			_clientBotList[client.getClientUsername()] = clientSocket;
			send(clientSocket, &IS_START, sizeof(IS_START), 0);
			return ;
		}
		else
		{
			send(clientSocket, &ALREADY_START, sizeof(ALREADY_START), 0);
			return ;
		}
	}
	else if (mode == "stop")
	{
		if (_clientBotList.count(client.getClientUsername()) == 1)
		{
			_clientBotList.erase(client.getClientUsername());
			send(clientSocket, &IS_STOP, sizeof(IS_STOP), 0);
			return ;
		}
		else
		{
			send(clientSocket, &ALREADY_STOP, sizeof(ALREADY_STOP), 0);
			return;
		}
	}
	return;
}