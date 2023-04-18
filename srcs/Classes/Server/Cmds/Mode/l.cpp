#include "../../Server.hpp"

void Server::_setChannelLimit(int clientSocket, Channel* channel, std::string channelName, std::string content)
{
    std::string message;
    char* pEnd;
    int limit = std::strtod(content.c_str(), &pEnd);
    if (limit < 0 || *pEnd != '\0')
    {
        message = "[ERROR]: Invalid value for channel limit\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    channel->setLimit(limit);
    message = "[INFO]: Channel " + channelName + " limit has been set\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}

void Server::_removeChannelLimit(int clientSocket, Channel* channel, std::string channelName)
{
    std::string message;
    channel->unsetLimit();
    message = "[INFO]: Channel " + channelName + " limit has been removed\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}