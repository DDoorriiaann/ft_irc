/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleClientEntrys.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:15:54 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/05 14:15:54 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Server.hpp"

int	Server::_handleClientEntry(Client &client, std::string clientEntry)
{
	std::string	cmd;
	int	found;
	(void)client;

	found  = clientEntry.find(" ", 0);
	cmd = clientEntry.substr(0, found);
	std::cout << cmd << std::endl;

	//if (cmd == "/msg")
	//	_sendPrivateChat();
	return (SUCCESS);
}

