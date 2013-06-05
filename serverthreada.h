#ifndef SERVER_THREAD_A_H
#define SERVER_THREAD_A_H
#include"serverthread.h"
#include"server.h"

class ServerThreadA : public ServerThread{
public:
	ServerThreadA();
	~ServerThreadA(){};
	void start(int fd);
	bool finished();
	int sockfd();
	pthread_t tid();
	void setkey(pthread_t t);
	pthread_t getkey();
	void threadExit();
private:
	pthread_t _tid;
	int _fd;
	bool _finished;
	Server* _server;
	//static void* _threadLoop(void *arg);
};

#endif
