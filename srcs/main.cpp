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

int	main(int ac, char **av)
{
	if (ac != 2 || checkPort(av[1]) == FAILURE)
		return (EXIT_FAILURE);

	Server	server(atoi(av[1])); // Run the server on the port -> av[1].
	manaTcpServer(server);
	return (EXIT_SUCCESS);
}
