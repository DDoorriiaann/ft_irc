#ifndef BOT_HPP
#define BOT_HPP

#include <pthread.h>

class Bot {
public:
	Bot();
	~Bot();

	void start();
	void stop();
	void join();

private:
	static void* display_funny_message(void* arg);

	pthread_t message_thread;
	bool continue_execution;
	pthread_mutex_t execution_mutex;
};

#endif // BOT_HPP
