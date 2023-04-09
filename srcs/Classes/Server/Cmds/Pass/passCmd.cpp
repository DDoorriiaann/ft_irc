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

#define BAD_PASSWORD 			"[ERROR]: Bad password.\n[INFO]: Use /cmd PASS to enter the password.\n"
#define	MSG_ENTER_USRNM			"[INFO]: Good password ✅\n[INFO]: Use /cmd USER <username> to finish the connection.\n"
#define USERNAME_ALREADY_SET 	"[ERROR] Username already set.\n"
#define SPACE_IN_USERNAME 		"[ERROR] Space in username.\n"
#define EMPTY_USERNAME 			"[ERROR] Empty username.\n"
#define	DISCONNECT				"[INFO] DISCONNECT.\n"
#define	PWD_ALREADY_PAST		"[ERROR]: Password has already been transmitted.\n"
#define	USE_USER_CMD			"[INFO]: Use /cmd USER <your username> to finish the connection.\n"

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
		return ;
	}

	if (clientStatus != PWD_ENTRY_STATUS)
	{
		send(clientSocket, &PWD_ALREADY_PAST, sizeof(PWD_ALREADY_PAST), 0);
		if (clientStatus == USERNAME_ENTRY_STATUS)
			send(clientSocket, &USE_USER_CMD, sizeof(USE_USER_CMD), 0);
		return ;
	}

	send(clientSocket, &MSG_ENTER_USRNM, sizeof(MSG_ENTER_USRNM), 0);
	client.setClientStatus(USERNAME_ENTRY_STATUS);
	std::cout << "Good PASSWORD" << std::endl;
	return ;
}