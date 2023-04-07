#include "../../Server.hpp"



void	Server::_kick(std::istringstream& iss, Client& client, int clientSocket)
{


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
	// vérifier que la channel dont on doit kick le user existe bel et bien
	if (!isValidChannel(channelName))
	{
		//envoyer un message expliquant que la channel n'existe pas
		message = "[ERROR]: Channel not found\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}



	std::string userToKick;
	iss >> userToKick;


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
		message = "[ERROR]: You are not an operator on this channel, you are not allowed kick users!\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}
	// vérifier si l'utilisateur existe dans la DB
	// si l'utilisateur n'existe pas on renvoie un message a l'opérateur
	if (!channel->hasUser(userToKick))
	{
		// envoyer un message informant que l'utilisateur demandé n'est pas trouvé sur la channel
		message = "[ERROR]: User not found\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}

	// si l'utilisateur existe on le kick
	channel->kickUser(userToKick);
	message = "[INFO]: You (" + userToKick + ") have been kicked from channel " + channelName + "\n";
	send(getClient(searchClient(userToKick)).getClientSocket(), message.c_str(), message.length(), 0);

	message = "[INFO]: User nammed " + userToKick + " has been kicked from channel " + channelName + "\n";
	send(clientSocket, message.c_str(), message.length(), 0);


	// si le stream contient une raison on envoie la raison à l'utilisateur qui se fait kick

}