#include"serverthreada.h"
#include"config.h"


struct fd_tid{
	int fd;
	pthread_t tid;
};

ServerThreadA::ServerThreadA(){
	_finished=false;
	_server=Server::instance();
}


void* _threadLoop(void* arg){
	char buf[BUFFER_SIZE];
	int n=0;
	ServerThreadA* th=(ServerThreadA*)th;
	while(1){
		memset(buf,0,BUFFER_SIZE);
		n=recv(th->sockfd(),buf,BUFFER_SIZE,0);
		if(n<=0){
			printf("thread %ld recv() failed\n",th->tid());
			break;
		}
		buf[n]='\0';
		if(buf[0]=='q'){
			break;
		}
		usleep(1000);
		printf("thread %ld recv msg : %s\n",th->tid(),buf);
		printf("latest thread is %ld\n",th->getkey());
		th->setkey(th->tid());
		pthread_t tid=th->tid();
		n=send(th->sockfd(),&(tid),sizeof(pthread_t),0);
		if(n<=0){
			printf("thread %ld send() failed\n",th->tid());
			break;
		}
	}
	th->threadExit();
	return ((void*)0);
}

void ServerThreadA::start(int fd){
	_fd=fd;

	pthread_create(&_tid,NULL,_threadLoop,(void*)this);
}

bool ServerThreadA::finished(){
	return _finished;
}

pthread_t ServerThreadA::tid(){
	return _tid;
}

void ServerThreadA::setkey(pthread_t t){
	_server->setkey(t);
}

pthread_t ServerThreadA::getkey(){
	return _server->getkey();
}

void ServerThreadA::threadExit(){
	close(_fd);
	_server->cleanThreads();
}

int ServerThreadA::sockfd(){
	return _fd;
}

