#include "../../Server.hpp"

void Server::_setChannelKey(int clientSocket, Channel* channel, std::string channelName, std::string content)
{
    std::string message;
    channel->setKey(content);
    message = "[INFO]: Channel " + channelName + " password has been set\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}

void Server::_removeChannelKey(int clientSocket, Channel* channel, std::string channelName)
{
    std::string message;
    channel->unsetKey();
    message = "[INFO]: Channel " + channelName + " password has been removed\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}