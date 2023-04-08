#include "../../Server.hpp"



void	Server::_part(std::istringstream& iss, Client& client, int clientSocket)
{

	std::string username = client.getClientUsername();
	std::string message;
	std::string channelName;
	iss >> channelName;
	if (channelName[0] != '#')
	{
		// envoyer un message expliquant que la channel doit commencer par #
		message = "[ERROR]: A channel name always start with a \'#\'\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}
	channelName = channelName.substr(1);
	// vérifier que la channel que l'on veut quitter existe bel et bien
	if (!leaveChannel(channelName, username))
	{
		//envoyer un message expliquant que la channel n'existe pas
		message = "[ERROR]: Channel not found OR you're not a member of this channel\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}

	// on a bien quitté la channel:
	message = "[INFO]: You were successfully removed from channel " + channelName + "\n";
	send(clientSocket, message.c_str(), message.length(), 0);
}