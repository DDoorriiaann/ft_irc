#include "Server.hpp"

Server::Server(void) //Canonical
{
	std::cout << "Server Constructeur called." << std::endl;
	return;
}

Server::Server(Server const& copy) //Canonical
{
	std::cout << "Server Constructeur called." << std::endl;
	*this = copy;
}

Server::~Server() //Canonical
{
	std::cout << "Server Destructeur called." << std::endl;
	return;
}

Server& Server::operator=(Server const& rhs) //Canonical
{
	if (this != &rhs)
	{
		this->_socketServer = rhs._socketServer;
	}
	return *this;
}

//////////////// GET ////////////////

Client& Server::getClient(int index)
{
	return (this->_client[index]);
}

int		Server::getServerSocket(void) const
{
	return (this->_socketServer);
}

int		Server::getNbrClient(void) const
{
	return (this->_nbrClient);
}

//////////////// SET ////////////////

void	Server::setClient(Client& client)
{
	this->_client.push_back(client);
	this->_nbrClient++;
	return;
}


/////////////// CHANNELS ////////////

bool Server::createChannel(const std::string& name) {
	if (_channels.find(name) == _channels.end()) {
		_channels[name] = Channel(name);
		return true;
	}
	return false;
}

bool Server::joinChannel(const std::string& channelName, const std::string& user) {
	std::map<std::string, Channel>::iterator it = _channels.find(channelName);
	int userSocket = _client[searchClient(user)].getClientSocket();

	if (it == _channels.end()) {
		// Si la channel n'existe pas, la créer et définir l'utilisateur comme opérateur
		Channel newChannel(channelName);
		newChannel.setOperator(user);
		newChannel.join(user);
		_channels.insert(std::make_pair(channelName, newChannel));
		std::cout << "New channel created : " << channelName << std::endl;

		std::string message = "You've just created a new channel : " + channelName + "\n";
		send(userSocket, message.c_str(), message.size(), 0);
	}
	else {
		// Sinon, rejoindre la channel existante
		it->second.join(user);
		std::string message = "You're now member of the channel " + channelName + "\n";
		send(userSocket, message.c_str(), message.size(), 0);
	}

	return true;
}

bool Server::leaveChannel(const std::string& channelName, const std::string& user) {
	std::map<std::string, Channel>::iterator it = _channels.find(channelName);

	if (it != _channels.end()) {
		bool isOperator = it->second.isOperator(user);
		it->second.leave(user);

		if (isOperator && it->second.operatorCount() == 0) {
			// Si l'utilisateur est le dernier opérateur, supprimer la channel
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

void Server::sendMessageToChannel(const std::string& channelName, const std::string& username, const std::string& message) {
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
		std::string fullMessage = "\n[" + channelName + "] " + username + ": " + message + "\n";

		//Envoyer le message à tous les utilisateurs de la channel
		std::set<std::string>::const_iterator it;
		for (it = users.begin(); it != users.end(); ++it) {
			const std::string& user = *it;

			// Récupérer le socket du client
			int clientSocket = _client[searchClient(user)].getClientSocket();

			if (clientSocket != -1 && clientSocket != senderSocket) {
				send(clientSocket, fullMessage.c_str(), fullMessage.size(), 0);
			}
		}
	}
	else {
		// La channel spécifiée n'existe pas , renvoyer un message d'erreur//

		std::string errorMessage = "channel not found\n";
		send(senderSocket, errorMessage.c_str(), errorMessage.size(), 0);
	}
}

//////////////// Function //////////////
int    Server::searchClient(std::string userName)

{
	int index;

	index = 0;
	while (index < _nbrClient)
	{
		if (_client[index].getClientUsername() == userName)
			return (index);
		index++;
	}
	return (-1);
}

void	Server::_unsetClient(Client& client)
{
	std::string	clientUsername;
	int	clientIndex;

	clientUsername = client.getClientUsername();
	clientIndex = searchClient(clientUsername);
	_client.erase(_client.begin() + clientIndex);
	return;
}