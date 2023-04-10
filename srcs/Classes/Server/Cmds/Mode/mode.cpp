#include "../../Server.hpp"

void	Server::_mode(std::istringstream& iss, Client& client, int clientSocket)
{


	std::string message;
	std::string flag;
	std::string channelName;

	iss >> flag;
	if (flag != "-o" && flag != "+o")
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

	std::string userToOp;
	iss >> userToOp;

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
	// vérifier si l'utilisateur existe dans la DB
	// si l'utilisateur n'existe pas on renvoie un message a l'opérateur
	if (!channel->hasUser(userToOp))
	{
		// envoyer un message informant que l'utilisateur demandé n'est pas trouvé sur la channel
		message = "[ERROR]: User not found\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}

	// si l'utilisateur existe on le kick
	if (flag == "-o")
	{
		if (!channel->isOperator(userToOp))
		{
			message = "[ERROR]: User is not an operator\n";
			send(clientSocket, message.c_str(), message.length(), 0);
			return;
		}
		channel->unsetOperator(userToOp);
		message = "[INFO]: You (" + userToOp + ") are not anymore an operator of the channel " + channelName + "\n";
		send(getClient(searchClient(userToOp)).getClientSocket(), message.c_str(), message.length(), 0);

		message = "[INFO]: User nammed " + userToOp + " is not anymore an operator of the channel " + channelName + "\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		if (channel->operatorCount() == 0)
			_kickAllUsersFromChannel(*channel);
	}

	else
	{
		if (channel->isOperator(userToOp))
		{
			message = "[ERROR]: User is already an operator\n";
			send(clientSocket, message.c_str(), message.length(), 0);
			return;
		}
		channel->setOperator(userToOp);
		message = "[INFO]: You (" + userToOp + ") are now an operator of the channel " + channelName + "\n";
		send(getClient(searchClient(userToOp)).getClientSocket(), message.c_str(), message.length(), 0);

		message = "[INFO]: User nammed " + userToOp + " is now an operator of the channel " + channelName + "\n";
		send(clientSocket, message.c_str(), message.length(), 0);
	}

}