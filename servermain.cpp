#include"server.h"

int main(){
	Server* server=Server::instance();
	server->start();
	return 0;
}
