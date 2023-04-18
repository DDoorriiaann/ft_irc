#include "../../Server.hpp"

void Server::_addOp(int clientSocket, Channel* channel, std::string channelName, std::string content)
{
    std::string message;
    // vérifier si l'utilisateur existe dans la DB
        // si l'utilisateur n'existe pas on renvoie un message a l'opérateur
    if (!channel->hasUser(content))
    {
        // envoyer un message informant que l'utilisateur demandé n'est pas trouvé sur la channel
        message = "[ERROR]: User not found\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    if (channel->isOperator(content))
    {
        message = "[ERROR]: User is already an operator\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    channel->setOperator(content);
    message = "[INFO]: You (" + content + ") are now an operator of the channel " + channelName + "\n";
    send(getClient(searchClient(content)).getClientSocket(), message.c_str(), message.length(), 0);

    message = "[INFO]: User nammed " + content + " is now an operator of the channel " + channelName + "\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}