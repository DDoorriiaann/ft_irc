/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:37:11 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/04 23:37:11 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "Server.hpp"

void	Server::init(int port, std::string pwd)
{
	struct	sockaddr_in	addrServer;

	_serverPwd = pwd;
	_socketServer = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketServer < 0) {
		std::cerr << "Error during socket creation" << std::endl;
		return;
	}

	_nbrClient = 0;

	// Enable reuse of same port after crash
	int enable = 1;
	if (setsockopt(_socketServer, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		std::cerr << "Error during socket configuration" << std::endl;
		return;
	}

	// This is the id of the socket.
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);

	if (bind(_socketServer, (const struct sockaddr*)&addrServer, sizeof(addrServer)) < 0) {
		std::cerr << "Error during socket binding" << std::endl;
		return;
	}

	if (listen(_socketServer, 10) < 0) {
		std::cerr << "Error during listen initialization" << std::endl;
		return;
	}

	std::cout << MSG_CREATION_SUCCESS << std::endl;
	return;
}
