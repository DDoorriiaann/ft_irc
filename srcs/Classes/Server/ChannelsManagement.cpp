#include "Server.hpp"

bool Server::createChannel(const std::string& name) {
	if (_channels.find(name) == _channels.end()) {
		_channels[name] = Channel(name);
		return true;
	}
	return false;
}

bool Server::joinChannel(const std::string& channelName, const std::string channelKey, const std::string& user) {
	std::map<std::string, Channel>::iterator it = _channels.find(channelName);
	int userSocket = _client[searchClient(user)].getClientSocket();

	if (it == _channels.end()) {
		// Si la channel n'existe pas, la créer et définir l'utilisateur comme opérateur
		Channel newChannel(channelName);
		newChannel.setOperator(user);
		newChannel.join(user);
		_channels.insert(std::make_pair(channelName, newChannel));
		if (channelKey != "")
			_channels[channelName].setKey(channelKey);
		std::cout << "New channel created : " << channelName << std::endl;
		std::string message = "You've just created a new channel : " + channelName + "\n";
		send(userSocket, message.c_str(), message.size(), 0);
	}
	else {
		// Sinon, rejoindre la channel existante
		if (it->second.isKeyProtected() && it->second.getKey() != channelKey) {
			std::string message = "[ERROR]: Wrong channel key\n";
			send(userSocket, message.c_str(), message.size(), 0);
			return false;
		}
		it->second.join(user);
		std::string message = "You're now member of the channel " + channelName + "\n";
		send(userSocket, message.c_str(), message.size(), 0);
	}

	return true;
}

void Server::_kickAllUsersFromChannel(Channel& channel)
{
	std::set<std::string>::iterator user = channel.getUsers().begin();
	std::string channelName = channel.getName();
	while (user != channel.getUsers().end())
	{
		std::string message = "[INFO]: You (" + *user + ") have been kicked from channel " + channelName + " because this channel was closed by its last operator\n";
		send(getClient(searchClient(*user)).getClientSocket(), message.c_str(), message.length(), 0);
		user++;
	}
	channel.clearUsers();
}

bool Server::leaveChannel(const std::string& channelName, const std::string& user) {
	std::map<std::string, Channel>::iterator it = _channels.find(channelName);

	if (it != _channels.end()) {
		bool isOperator = it->second.isOperator(user);
		it->second.leave(user, isOperator);

		if (isOperator && it->second.operatorCount() == 0) {
			// Si l'utilisateur est le dernier opérateur, supprimer la channel et kick tous les users
			_kickAllUsersFromChannel(it->second);
			std::cout << "Channel " << channelName << " has been deleted" << std::endl;
			_channels.erase(it);
		}
		return true;
	}
	return false;
}

bool Server::isValidChannel(const std::string& channelName) const {
	return  _channels.find(channelName) != _channels.end();
}

Channel* Server::getChannel(const std::string& channelName) {
	if (isValidChannel(channelName))
		return &(_channels.find(channelName)->second);
	else
		return NULL;
}

const std::string Server::getChannelListAsString(void) const
{
	std::string channelList;
	std::map<std::string, Channel>::const_iterator it = _channels.begin();
	while (it != _channels.end())
	{
		channelList.append(it->first);
		it++;
	}
	return channelList;
}

const std::map<std::string, Channel>& Server::getChannels() const {
	return _channels;
}

////// SEND MESSAGES /////////

void Server::sendMessageToChannel(const std::string& channelName, const std::string& username, const std::string& fullName, const std::string& message) {
	// Rechercher la channel spécifiée
	std::map<std::string, Channel>::iterator it = _channels.find(channelName);
	int senderSocket = _client[searchClient(username)].getClientSocket();

	if (it != _channels.end()) {
		// Channel trouvée
		// Recupérer la liste des users du channel
		Channel& channel = it->second;
		std::set<std::string> users = channel.getUsers();

		// Vérifier si le sender est membre de la channel
		if (users.find(username) == users.end())
		{
			std::string errorMessage;
			errorMessage.append(HEADER_ERROR).append("Message not sent because you are not member of the channel ").append(channelName).append("\n");
			send(senderSocket, errorMessage.c_str(), errorMessage.size(), 0);
			return;
		}

		// Construire le message complet à envoyer
		std::string fullMessage = "[" + channelName + "] " + fullName + ": " + message + "\n";

		//Envoyer le message à tous les utilisateurs de la channel
		std::set<std::string>::const_iterator it;
		for (it = users.begin(); it != users.end(); ++it) {
			const std::string& user = *it;

			// Récupérer le socket du client
			int clientSocket = _client[searchClient(user)].getClientSocket();
			if (clientSocket != -1)
				send(clientSocket, fullMessage.c_str(), fullMessage.size(), 0);
		}
	}
	else {
		// La channel spécifiée n'existe pas , renvoyer un message d'erreur//

		std::string errorMessage = "channel not found\n";
		send(senderSocket, errorMessage.c_str(), errorMessage.size(), 0);
	}
}