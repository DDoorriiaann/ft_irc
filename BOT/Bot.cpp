/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtelnoff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:08:16 by gtelnoff          #+#    #+#             */
/*   Updated: 2023/04/10 01:08:17 by gtelnoff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <map>
#include <sstream>
#include <signal.h>

static void load_messages(std::vector<std::string>& messages);
void sigint_handler(int sig);

bool quit = false;

int	main(int ac, char** av)
{
	struct	sockaddr_in			addrClient;
	std::vector<std::string>	funny_messages;
	std::string					password;
	std::string					message;
	int							port;
	int							socketClient;
	int 						nb_messages;
	int							index;

	if (ac != 3)
		return (1);
	password = "/cmd PASS ";
	password += av[2];
	password += "\n";
	port = atoi(av[1]);
	socketClient = socket(AF_INET, SOCK_STREAM, 0);
	if (socketClient < 0) {
		std::cerr << "Error during socket creation" << std::endl;
		return 1;
	}

	// This is the id of the socket.
	addrClient.sin_addr.s_addr = htonl(INADDR_ANY);
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(port);

	//connect(socketClient, (const struct sockaddr*)&addrClient, sizeof(addrClient));
	if (connect(socketClient, (const struct sockaddr*)&addrClient, sizeof(addrClient)) < 0) {
		std::cerr << "Error during connection to server" << std::endl;
		close(socketClient);
		return 1;
	}
	// Gérer le signal ctrl-c (SIGINT)
	signal(SIGINT, sigint_handler);

	//// Bot connect to the server
	send(socketClient, password.c_str(), password.length(), 0);
	sleep(2);
	send(socketClient, &"/cmd USER PasEncore13h13Bot\n", sizeof("/cmd USER PasEncore13h13Bot\n"), 0);

	load_messages(funny_messages);
	nb_messages = funny_messages.size();
	while (quit == false)
	{
		index = rand() % nb_messages;
		message = funny_messages[index] + "\n";
		send(socketClient, message.c_str(), message.length(), 0);
		sleep(10);
	}
	message = "QUIT\n";
	send(socketClient, message.c_str(), message.length(), 0);
	return (0);
}

void sigint_handler(int sig)
{
	if (sig == SIGINT)
		quit = true;
}

static void load_messages(std::vector<std::string>& messages)
{
	messages.push_back("Not 13:13, try again.\n");
	messages.push_back("It's almost not 13:13.\n");
	messages.push_back("Wait, uh no, not 13:13.\n");
	messages.push_back("Nice try, but it's not 13:13.\n");
	messages.push_back("Nope, still not 13:13.\n");
	messages.push_back("13:13? Not yet!\n");
	messages.push_back("Almost there, but not 13:13.\n");
	messages.push_back("Getting closer, but not 13:13.\n");
	messages.push_back("13:13? Maybe later.\n");
	messages.push_back("Hmm, not 13:13.\n");
	messages.push_back("Not quite 13:13.\n");
	messages.push_back("Hold on, not 13:13 yet.\n");
	messages.push_back("13:13? Not so fast!\n");
	messages.push_back("It's not 13:13, but nice guess.\n");
	messages.push_back("Close, but no 13:13.\n");
	messages.push_back("Keep trying, not 13:13.\n");
	messages.push_back("13:13 is still hiding.\n");
	messages.push_back("13:13? Not quite.\n");
	messages.push_back("You're not 13:13, but close.\n");
	messages.push_back("Good effort, but it's not 13:13.\n");
	messages.push_back("13:13? Not this time!\n");
	messages.push_back("Almost 13:13, but not quite.\n");
	messages.push_back("13:13? You'll have to wait.\n");
	messages.push_back("A little bit more, and it's 13:13.\n");
	messages.push_back("Not 13:13, but you're getting warmer!\n");
	messages.push_back("13:13? Not on my watch!\n");
	messages.push_back("Keep guessing, it's not 13:13 yet.\n");
	messages.push_back("Is it 13:13? Nope!\n");
	messages.push_back("Oh, so close! But not 13:13.\n");
	messages.push_back("It's not 13:13, but keep trying!\n");
	messages.push_back("13:13? Not in this timeline!\n");
	messages.push_back("Not 13:13, but you're persistent!\n");
	messages.push_back("13:13? Good guess, but no.\n");
	messages.push_back("Maybe next time, it's not 13:13.\n");
	messages.push_back("No 13:13 here, try again later.\n");
}
