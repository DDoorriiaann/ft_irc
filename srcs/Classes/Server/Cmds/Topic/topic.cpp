#include "../../Server.hpp"

void Server::_topic(std::istringstream& iss, Client& client, int clientSocket)
{
    std::string message;
    std::string channelName;
    iss >> channelName;
    if (channelName[0] != '#')
    {
        // envoyer un message expliquant que la channel doit commencer par #
        message = "[ERROR]: A channel name always start with a \'#\'\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    channelName = channelName.substr(1);
    // vérifier que la channel dont on doit kick le user existe bel et bien
    if (!isValidChannel(channelName))
    {
        //envoyer un message expliquant que la channel n'existe pas
        message = "[ERROR]: Channel not found\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    Channel* channel = getChannel(channelName);
    if (!channel)
    {
        message = "[ERROR]: Channel not found\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    std::string content;
    std::string firstPart;
    std::string lastPart;
    iss >> firstPart;
    getline(iss, lastPart);
    content = firstPart + lastPart;
    if (content.empty())
    {
        std::string topic = channel->getTopic().empty() ? "No topic is set" : channel->getTopic();
        message = "[INFO]: channel " + channelName + " topic is: " + topic + "\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    if (channel->isTopicProtected() && !channel->isOperator(client.getClientUsername()))
    {
        message = "[ERROR]: You are not allowed to change the topic\n";
        send(clientSocket, message.c_str(), message.length(), 0);
        return;
    }
    channel->setTopic(content);
    message = "[INFO]: Topic has been set\n";
    send(clientSocket, message.c_str(), message.length(), 0);
}