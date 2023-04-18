#include "../../Server.hpp"

void Server::_setTopicProtection(int clientSocket, Channel* channel, std::string channelName)
{
    std::string message;
    channel->setTopicProtection();
    message = "[INFO]: Channel " + channelName + " topic protection has been set\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}

void Server::_removeTopicProtection(int clientSocket, Channel* channel, std::string channelName)
{
    std::string message;
    channel->unsetTopicProtection();
    message = "[INFO]: Channel " + channelName + " topic protection has been removed\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}