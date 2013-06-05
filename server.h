#ifndef SERVER_H
#define SERVER_H
#include"config.h"
#include"serverthread.h"
#include<list>
class Server{

public:
    static Server* instance();
	void start();
	~Server();
	void setkey(pthread_t v);
	pthread_t getkey();
	void cleanThreads();
protected:
	Server();
private:

	pthread_t _key;
	pthread_mutex_t _mutex;
	pthread_mutex_t _threads_mutex;
	std::list<ServerThread*> _threads;	
};

#endif
