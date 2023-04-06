/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkWhiteSpace.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 10:26:36 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/06 10:26:37 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Classes/Server/Server.hpp"

int	checkNoWhiteSpace(std::string str)
{
	for(int i = 0; str[i] != '\0'; i++)
		if (isspace(str[i]))
			return (FAILURE);
	return (SUCCESS);
}
