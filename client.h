#ifndef CLIENT_H
#define CLIENT_H

#include"config.h"

class Client{
public:
	Client();
	void start();
private:
	struct sockaddr_un _remote;
	int _sock;
};

#endif
