/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:13:43 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/03 11:13:45 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <string>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

int	createServer(int port)
{
	struct	sockaddr_in	addrServer;
	int 				sockFd;

	sockFd = socket(AF_INET, SOCK_STREAM, 0);

	addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);

	bind(sockFd, (const struct sockaddr *)&addrServer, sizeof(addrServer));
	listen(sockFd, 10);
	std::cout << "\033[1;32m🎉 The server as been create successfuly 🎉\033[0m" << std::endl;
	return (sockFd);
}

int	main(int ac, char **av)
{
	int					ret;
	struct	sockaddr_in	addrClient;
	int 				sockFd;
	int					socketClient[10];
	int					retSel;
	int					maxClient;
	char				Buf[1024];
	int					i;
	fd_set 				read_fd_set;
	socklen_t 			csize = sizeof(socketClient);

	sockFd = createServer(atoi(av[1]));
	maxClient = 10;
	i = 0;
	while (1)
	{
		FD_ZERO(&read_fd_set);
		FD_SET(sockFd, &read_fd_set);
		if (i != 0)
		{
			FD_SET(socketClient[0], &read_fd_set);
			retSel = select(socketClient[0] + 1, &read_fd_set, NULL, NULL, NULL);
		}
		else
			retSel = select(sockFd + 1, &read_fd_set, NULL, NULL, NULL);
		if (retSel)
		{
			if (FD_ISSET(sockFd, &read_fd_set))
			{
				socketClient[i] = accept(sockFd, (struct sockaddr*)&addrClient, &csize);
				send(socketClient[i], &"Bienvenue !\n", sizeof("Bienvenue !\n"), 0);
				i++;
			}
			if (FD_ISSET(socketClient[0], &read_fd_set))
			{
				ret = recv(socketClient[0], &Buf, sizeof(Buf), 0);
				Buf[ret] = '\0';
				std::cout << Buf << std::endl;
			}
		}

	}
	return (0);
}
