#include "../../Server.hpp"

void	Server::_bot(std::istringstream& iss, int clientSocket)
{
	std::string	command;
	std::string message;

	getline(iss, command);
	command = command.substr(1); // Delete the space.
	std::cout << "command is: " << command << std::endl; // !DEBUG
	if (command != "start" && command != "stop")
	{
		message += HEADER_ERROR;
		message += "Unknown command.\n";
		send(clientSocket, message.c_str(), message.length(), 0);
		return;
	}


	///// SUCCESS
	if (command == "start")
	{
		if (_theBot == NULL)
			startBot();
		else
		{
			message += HEADER_ERROR;
			message += "The bot is already running.\n";
			send(clientSocket, message.c_str(), message.length(), 0);
			return;
		}
	}
	else
	{
		if (_theBot != NULL)
			stopBot();
		else
		{
			message += HEADER_ERROR;
			message += "The bot is not running.\n";
			send(clientSocket, message.c_str(), message.length(), 0);
			return;
		}
	}
	message = "The bot is online, it will send a message to everyone every 10 seconds.\n";
	send(clientSocket, message.c_str(), message.length(), 0);
	return;
}