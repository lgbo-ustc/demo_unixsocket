#include"config.h"

#define BUF_SIZE 10

void *loop(void* s){
	char buf[BUF_SIZE];
	int n=0;
	unsigned int socketfd=*(( int *)s);
	printf("a new thread in server\n");
	
	while(1){
		memset(buf,'\0',BUF_SIZE);
		n=recv(socketfd,buf,BUF_SIZE,0);
		if(n==-1||n==0){
			perror("thread:recv() failed");
			break;
			//continue;
		}
		usleep(1000);
		printf("server thread :revice msg: %s %d\n",buf,n);
		if(buf[0]=='q'){
			break;
		}
		printf("server thread:trying to send :");
		n=send(socketfd,buf,strlen(buf),0);
		if(n<=0){
			perror("server thread:send() failed");
			break;
			//continue;
		}
		printf(" %s\n",buf);
		memset(buf,0,BUF_SIZE);
	}
	printf("server thread:close\n");
	close(socketfd);

}

int main(){
	int s_socket,c_socket;
	/*
	struct sockaddr_un{ 
		short sun_family; //AF_UNIX 
        char  sun_PATH[108]; //path name
    }; 
	*/
	struct sockaddr_un local,remote;
	int len;
	pthread_t tid;

	/*
	The AF_UNIX (also known as AF_LOCAL) socket family is used to
    communicate between processes on the same machine efficiently.
	*/
	if((s_socket=socket(AF_UNIX,SOCK_STREAM,0))==-1){
		perror("server:socket() failed");
		exit(1);
	}
	local.sun_family=AF_UNIX;
	//SOCKET_PATH is defined is config.h.
	strcpy(local.sun_path,SOCKET_PATH);
	/*
	call unlink() before bind() to remove the socket if it already exists. 
	*/
	unlink(local.sun_path);
	len=strlen(local.sun_path)+sizeof(local.sun_family);
	/*
	bind the socket to an address in the Unix domain. (That address
	 is a special file on disk.)
	*/
	if(bind(s_socket,(struct sockaddr*)&local,len)==-1){
		perror("server:bind() failed");
		exit(1);
	}
	/*
	This instructs the socket to listen for incoming connections from client programs.
	second argument is maxium length of queue of  clients connecting to server.
	*/
	if(listen(s_socket,5)==-1){
		perror("server:listen failed");
		exit(1);
	}
	/*
	listening loop 
	*/
	while(1){
		printf("sever:wait for  a connection ...\n");
		int t=sizeof(remote);
		/*
		what would cause the error?
		*/
		if((c_socket=accept(s_socket,(struct sockaddr*)&remote,&t))==-1){
			perror("server:accept failed");
			break;
		}
		printf("server:connected\n");
		pthread_create(&tid,NULL,loop,(void*)&c_socket);
		printf("create a new thread\n");
		/*
		unlike using fork(),we should not close the c_socket here 
		*/

	}
	printf("server:close\n");
	return 0;
}
