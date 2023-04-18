#include "../../Server.hpp"

static bool isValidFlag(std::string flag)
{
	if (flag == "-o" || flag == "+o" || flag == "-k" || flag == "+k" || flag == "-l" || flag == "+l" || flag == "-t" || flag == "+t" || flag == "-i" || flag == "+i")
		return true;
	return false;
}

void	Server::_mode(std::istringstream& iss, Client& client, int clientSocket)
{
	std::string message;
	std::string flag;
	std::string channelName;

	iss >> flag;

	if (isValidFlag(flag) == false)
	{
		message = "[ERROR]: Invalid flag\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}

	iss >> channelName;
	if (channelName[0] != '#')
	{
		// envoyer un message expliquant que la channel doit commencer par #
		message = "[ERROR]: A channel name always start with a \'#\'\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}
	channelName = channelName.substr(1);
	// vérifier que la channel sur laquelle on veut op le user existe bel et bien
	if (!isValidChannel(channelName))
	{
		//envoyer un message expliquant que la channel n'existe pas
		message = "[ERROR]: Channel not found\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}

	std::string content;
	std::string firstPart;
	std::string lastPart;
	iss >> firstPart;
	getline(iss, lastPart);
	content = firstPart + lastPart;

	std::cout << "content : " << content << std::endl;
	if ((flag[1] == 'o' || flag == "+k" || flag == "+l") && content.empty())
	{
		message = "[ERROR]: missing parameter\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}

	Channel* channel = getChannel(channelName);
	if (!channel)
	{
		//envoyer une message disant que la channel n'existe plus
		message = "[ERROR]: Channel not found\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}
	// vérifier que la requête provient d'un opérateur et ne concerne pas un opérateur
	if (!channel->isOperator(client.getClientUsername()))
	{
		message = "[ERROR]: You are not an operator on this channel, you are not allowed set users as operators!\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}

	if (flag == "-o")
		_removeOp(clientSocket, channel, channelName, content);
	else if (flag == "+o")
		_addOp(clientSocket, channel, channelName, content);
	else if (flag == "+k")
		_setChannelKey(clientSocket, channel, channelName, content);
	else if (flag == "-k")
		_removeChannelKey(clientSocket, channel, channelName);
}