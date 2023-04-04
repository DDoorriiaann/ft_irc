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
	if (port < 0 || port > 65535)
	{
		std::cerr << "[ERROR] The port is beyond the range.\n[INFO] Use port from 1023 to 65535." << std::endl;
		return (FAILURE);
	}
	if (port > 0 && port < 1023)
	{
		std::cerr << "[ERROR] This port is inaccessible.\n[INFO] Use port from 1023 to 65535." << std::endl;
		return (FAILURE);
	}
	return (SUCCESS);
}
