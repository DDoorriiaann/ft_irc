#include "../../Server.hpp"

void Server::_setInviteOnly(int clientSocket, Channel* channel, std::string channelName)
{
    std::string message;
    channel->setInviteOnly();
    message = "[INFO]: Channel " + channelName + " is now invite only\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}

void Server::_unsetInviteOnly(int clientSocket, Channel* channel, std::string channelName)
{
    std::string message;
    channel->unsetInviteOnly();
    message = "[INFO]: Channel " + channelName + " is no longer invite only\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}