#include"server.h"
#include"serverthreadfactory.h"

using namespace std;

static Server* _instance=NULL;

Server::Server(){
	_key=0;
	pthread_mutex_init(&_mutex, NULL);
	pthread_mutex_init(&_threads_mutex,NULL);
}
/*
 *use singleton method to make sure that
 *there is always only one instance of Server. 
 *
 */

Server* Server::instance(){
	if(_instance==NULL){
		_instance=new Server;
	}
	return _instance;
}


Server::~Server(){

}

/*
   the operation of writing or reading _key
   must be atomic
*/
void Server::setkey(pthread_t v){
	pthread_mutex_lock(&_mutex);
	_key=v;
	pthread_mutex_unlock(&_mutex);
} 

pthread_t Server::getkey(){
	pthread_t key;
	pthread_mutex_lock(&_mutex);
	key=_key;
	pthread_mutex_unlock(&_mutex);
	return key;
}

void Server::start(){
	int s_socket,c_socket,len;
	struct sockaddr_un local,remote;
	char buf[BUFFER_SIZE];
	int n=0;
	if((s_socket=socket(AF_UNIX,SOCK_STREAM,0))==-1){
		std::cout<<"server : socket() error!"<<std::endl;
		return;
	}
	local.sun_family=AF_UNIX;
	strcpy(local.sun_path,SOCKET_PATH);
	unlink(local.sun_path);
	len=strlen(local.sun_path)+sizeof(local.sun_family);
	if(bind(s_socket,(struct sockaddr*)&local,len)==-1){
		std::cout<<"server:bind() error"<<std::endl;
		return;
	}
	if(listen(s_socket,5)==-1){
		std::cout<<"server:listen error"<<std::endl;
		return;
	}
	while(1){
		std::cout<<"server : waiting for a new connection ..."<<std::endl;
		len=sizeof(remote);
		if((c_socket=accept(s_socket,(struct sockaddr*)&remote,(socklen_t*)&len))==-1){
			std::cout<<"sever : accept() error"<<std::endl;
			return;
		}
		std::cout<<"server : connected"<<std::endl;
		memset(buf,0,BUFFER_SIZE);
		n=recv(c_socket,buf,BUFFER_SIZE,0);
		if(n<=0){
			std::cout<<"server : recv() error"<<std::endl;
			close(c_socket);
			continue;
		}
		int flag = 0;
		memcpy(&flag,buf,sizeof(flag));
		ServerThread* th = ServerThreadFactory::createThread(flag);
		_threads.push_back(th);
		std::cout<<"server : create a new thread"<<std::endl;
		th->start(c_socket);
	}
}

void Server::cleanThreads(){
	pthread_mutex_lock(&_threads_mutex);
	for(list<ServerThread*>::iterator it=_threads.begin();
			it!=_threads.end();){
		if((ServerThread*)(*it)->finished()){
			ServerThread* th=(ServerThread*)(*it);
			_threads.erase(it++);
			delete th;
		}
		else{
			it++;
		}
	}
	pthread_mutex_unlock(&_threads_mutex);
}
