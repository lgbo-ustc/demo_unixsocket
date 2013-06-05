#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H
#include"config.h"

class ServerThread{
public:
	ServerThread(){};
	virtual ~ServerThread(){};

	virtual void start(int fd);
	virtual bool finished();
};

#endif
