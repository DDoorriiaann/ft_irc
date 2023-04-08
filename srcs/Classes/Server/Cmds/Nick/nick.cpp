/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:19:32 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/06 10:19:34 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Server.hpp"

int		checkNoWhiteSpace(std::string str);

void	Server::_nick(std::istringstream& iss, Client& client, int clientSocket)
{
	std::string	nickName;
	std::string message;

	getline(iss, nickName);
	nickName = nickName.substr(1);
	if (checkNoWhiteSpace(nickName) == FAILURE)
	{
		message += HEADER_ERROR;
		message += "Nicknames with spaces are not allowed.\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}

	///// SUCCESS

	client.setNickName(nickName);
	message += HEADER_INFO;
	message += "You are known now with the nick name: " + client.getFullName() + ".\n";
	send(clientSocket, message.c_str(), message.length(), 0);
	return;
}