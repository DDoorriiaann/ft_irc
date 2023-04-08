#include "Bot.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <vector>

Bot::Bot(): continue_execution(true) {
	pthread_mutex_init(&execution_mutex, NULL);
}

Bot::~Bot() {
	pthread_mutex_destroy(&execution_mutex);
}

void Bot::start() {
	pthread_create(&message_thread, NULL, display_funny_message, this);
}

void Bot::stop() {
	pthread_mutex_lock(&execution_mutex);
	continue_execution = false;
	pthread_mutex_unlock(&execution_mutex);
}

void Bot::join() {
	pthread_join(message_thread, NULL);
}

static void load_messages(std::vector<std::string>& messages)
{
	messages.push_back("Not 13:13, try again.");
	messages.push_back("It's almost not 13:13.");
	messages.push_back("Wait, uh no, not 13:13.");
	messages.push_back("Nice try, but it's not 13:13.");
	messages.push_back("Nope, still not 13:13.");
	messages.push_back("13:13? Not yet!");
	messages.push_back("Almost there, but not 13:13.");
	messages.push_back("Getting closer, but not 13:13.");
	messages.push_back("13:13? Maybe later.");
	messages.push_back("Hmm, not 13:13.");
	messages.push_back("Not quite 13:13.");
	messages.push_back("Hold on, not 13:13 yet.");
	messages.push_back("13:13? Not so fast!");
	messages.push_back("It's not 13:13, but nice guess.");
	messages.push_back("Close, but no 13:13.");
	messages.push_back("Keep trying, not 13:13.");
	messages.push_back("13:13 is still hiding.");
	messages.push_back("13:13? Not quite.");
	messages.push_back("You're not 13:13, but close.");
	messages.push_back("Good effort, but it's not 13:13.");
	messages.push_back("13:13? Not this time!");
	messages.push_back("Almost 13:13, but not quite.");
	messages.push_back("13:13? You'll have to wait.");
	messages.push_back("A little bit more, and it's 13:13.");
	messages.push_back("Not 13:13, but you're getting warmer!");
	messages.push_back("13:13? Not on my watch!");
	messages.push_back("Keep guessing, it's not 13:13 yet.");
	messages.push_back("Is it 13:13? Nope!");
	messages.push_back("Oh, so close! But not 13:13.");
	messages.push_back("It's not 13:13, but keep trying!");
	messages.push_back("13:13? Not in this timeline!");
	messages.push_back("Not 13:13, but you're persistent!");
	messages.push_back("13:13? Good guess, but no.");
	messages.push_back("Maybe next time, it's not 13:13.");
	messages.push_back("No 13:13 here, try again later.");
}

void* Bot::display_funny_message(void* arg) {
	Bot* bot = static_cast<Bot*>(arg);
	std::vector<std::string> funny_messages;

	load_messages(funny_messages);
	int nb_messages = funny_messages.size();

	while (true) {
		pthread_mutex_lock(&bot->execution_mutex);
		bool should_continue = bot->continue_execution;
		pthread_mutex_unlock(&bot->execution_mutex);

		if (!should_continue) {
			break;
		}

		time_t now = time(0);
		tm* local_time = localtime(&now);
		if (local_time->tm_hour == 13 && local_time->tm_min == 13) {
			std::cout << "It's 13:13!" << std::endl;
		}
		else {
			int index = rand() % nb_messages;
			std::cout << funny_messages[index] << std::endl;
		}
		sleep(10);
	}

	return NULL;
}
