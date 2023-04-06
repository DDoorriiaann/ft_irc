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
#include "Classes/Irc/Irc.hpp"
#include "Classes/Server/Server.hpp"
#include "Classes/Client/Client.hpp"

#define	PORT_INDEX 1
#define	PWD_INDEX 2

int	main(int ac, char **av)
{
	Server	server; // Run the server on the port -> av[1].

	if (ac != 3)
	{
		std::cerr << "\033[1;31m[ERROR]\033[0m: Some information is missing to launch the server.\n\033[1;32m[INFO]\033[0m: Use ./ircserv <port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}
	if (checkPort(av[PORT_INDEX]) == FAILURE)
		return (EXIT_FAILURE);

	server.init(atoi(av[PORT_INDEX]), av[PWD_INDEX]);
	server.run();
	return (EXIT_SUCCESS);
}
