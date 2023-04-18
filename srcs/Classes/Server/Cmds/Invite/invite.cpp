#include "../../Server.hpp"

void Server::_invite(std::istringstream& iss, Client& client, int clientSocket)
{
    std::string message;
    std::string channelName;
    std::string userToInvite;

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
    iss >> userToInvite;
    if (searchClient(userToInvite) < 0)
    {
        //envoyer un message expliquant que le nickname n'existe pas
        message = "[ERROR]: User not found\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    Channel* channel = getChannel(channelName);
    if (!channel)
    {
        //envoyer un message disant que la channel n'existe plus
        message = "[ERROR]: Channel not found\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    if (channel->isInviteOnly() == false)
    {
        //envoyer un message expliquant que la channel n'est pas invite only
        message = "[ERROR]: Channel is not invite only\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    if (channel->hasUser(client.getClientUsername()) == false)
    {
        //envoyer un message expliquant que le user n'est pas dans la channel
        message = "[ERROR]: You are not in this channel\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    if (channel->hasUser(userToInvite) == true)
    {
        //envoyer un message expliquant que le user est déjà dans la channel
        message = "[ERROR]: User is already in this channel\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    if (channel->isOperator(client.getClientUsername()) == false)
    {
        //envoyer un message expliquant que le user n'est pas op dans la channel
        message = "[ERROR]: You are not an operator in this channel\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    //ajouter le user à la liste des invitations de la channel
    channel->invite(userToInvite);
    //envoyer un message à l'userToInvite pour l'inviter dans la channel
    message = "You have been invited to join " + channelName + " by " + client.getClientUsername() + "\n";
    send(getClient(searchClient(userToInvite)).getClientSocket(), message.c_str(), message.length(), 0);
    //envoyer un message à l'opérateur pour lui dire que l'invitation a été envoyée
    message = "Invitation sent to " + userToInvite + "\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}