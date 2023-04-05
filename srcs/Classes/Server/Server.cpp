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

	if (it == _channels.end()) {
		// Si la channel n'existe pas, la créer et définir l'utilisateur comme opérateur
		Channel newChannel(channelName);
		newChannel.setOperator(user);
		_channels.insert(std::make_pair(channelName, newChannel));
	}
	else {
		// Sinon, rejoindre la channel existante
		it->second.join(user);
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


const std::map<std::string, Channel>& Server::getChannels() const {
	return _channels;
}

////// SEND MESSAGES /////////

void Server::sendMessageToChannel(const std::string& channelName, const std::string& username, const std::string& message) {
	// Rechercher la channel spécifiée
	std::map<std::string, Channel>::iterator it = _channels.find(channelName);

	if (it != _channels.end()) {
		// Channel trouvée
		Channel& channel = it->second;
		std::set<std::string> users = channel.getUsers();

		// Construire le message complet à envoyer
		std::string fullMessage = "[" + channelName + "] " + username + ": " + message;

		// Envoyer le message à tous les utilisateurs de la channel
		// for (const std::string& user : users) {
		// 	// Récupérer le socket du client (vous devez implémenter cette fonction getClientSocketByUsername)
		// 	int clientSocket = 1; //getClientSocketByUsername(user);

		// 	if (clientSocket != -1) {
		// 		send(clientSocket, fullMessage.c_str(), fullMessage.size(), 0);
		// 	}
		// }
	}
	else {
		// La channel spécifiée n'existe pas , renvoyer un message d'erreur//
	}
}

//////////////// Function //////////////
int	Server::searchClient(std::string userName)
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