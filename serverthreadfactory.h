#ifndef SERVER_THREAD_FACTORY_H
#define SERVER_THREAD_FACTORY_H
#include"config.h"
#include"serverthread.h"
class ServerThreadFactory{
public:
	static ServerThread* createThread(int flag);
};

#endif
