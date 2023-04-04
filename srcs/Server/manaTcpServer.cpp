/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manaTcpServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:06:28 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/04 15:06:29 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Classes/Irc/Irc.hpp"
#include "../Classes/Server/Server.hpp"
#include "../Classes/Client/Client.hpp"

int		resetFd(Server &server, fd_set	&read_fd_set);
void	addUser(Server &server, socklen_t csize, sockaddr_in addrClient);
void	processChatEntry(Client client, int clientSocket);

void	manaTcpServer(Server &server)
{
	struct		sockaddr_in	addrClient;
	fd_set					read_fd_set;
	socklen_t				csize;
	int						ret;
	int						lastFd;
	int						serverSocket;
	int						nbrClient;

	serverSocket = server.getServerSocket();
	csize = sizeof(int);
	while (1)
	{
		lastFd = resetFd(server, read_fd_set);
		ret = select(lastFd + 1, &read_fd_set, NULL, NULL, NULL);
		if (ret)
		{
			if (FD_ISSET(serverSocket, &read_fd_set))
				addUser(server, csize, addrClient);
			nbrClient = server.getNbrClient();
			for	(int i = 0; i < nbrClient; i++)
			{
				if (FD_ISSET(server.getClient(i).getClientSocket(), &read_fd_set))
					processChatEntry(server.getClient(i), server.getClient(i).getClientSocket());
			}
		}
	}
	return ;
}

int	resetFd(Server &server, fd_set	&read_fd_set)
{
	int	nbrClient;

	nbrClient = server.getNbrClient();

	FD_ZERO(&read_fd_set);
	FD_SET(server.getServerSocket(), &read_fd_set);

	for (int i = 0; i < nbrClient; i++)
		FD_SET(server.getClient(i).getClientSocket(), &read_fd_set);

	if (nbrClient == 0)
		return (server.getServerSocket());
	return (server.getClient(nbrClient - 1).getClientSocket()); // this return is for keep the last FD_SET use in select() func
}

void	addUser(Server &server, socklen_t csize, sockaddr_in addrClient)
{
	Client	client("unknown");
	int		serverSocket;	

	serverSocket = server.getServerSocket();
	client.setClientSocket(accept(serverSocket, (struct sockaddr*)&addrClient, &csize));
	server.setClient(client);
	send(client.getClientSocket(), &MSG_CONNECTED, sizeof(MSG_CONNECTED), 0);
	std::cout << NEW_USER_MSG << std::endl;
	return ;
}

void	processChatEntry(Client client, int clientSocket)
{
	int		ret;
	char	buf[1024];

	ret = recv(clientSocket, &buf, sizeof(buf), 0);
	buf[ret] = '\0';
	send(clientSocket, &MSG_SENT_SUCCESS, sizeof(MSG_SENT_SUCCESS), 0);

	std::cout << client.getClientUsername() << ": "<< buf;
}
