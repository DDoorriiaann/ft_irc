/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ckeckPort.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:36:25 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/04 10:36:26 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../Classes/Irc/Irc.hpp"

int	checkPort(char *stringPort)
{
	int	port;

	port = atoi(stringPort);
	if (port < 1024 || port > 65535)
	{
		std::cerr << "\033[1;31m[ERROR]\033[0m: The port is beyond the range.\n\033[1;32m[INFO]\033[0m: Use port from 1024 to 65535." << std::endl;
		return (FAILURE);
	}
	return (SUCCESS);
}
