#include"client.h"

Client::Client(){
	
}

void Client::start(){
	char buf[BUFFER_SIZE]={0};
	int n=0,len=0;
	
	if((_sock=socket(AF_UNIX,SOCK_STREAM,0))==-1){
		perror("client socket() failed\n");
		return;
	}
	printf("client is trying to connect to the server ...\n");
	_remote.sun_family=AF_UNIX;
	strcpy(remote.sun_path,SOCKET_PATH);
	len=strlen(remote.sun_path)+sizeof(remote.sun_family);
	if(connect(_sock,(struct sockaddr*)&remote,len)==-1){
		perror("client connect failed\n");
		return;
	}
	printf("client connected\n");
	n=1;
	n=send(_sock,&n,sizeof(n),0);
	if(n<=0){
		perror("client send1 failed\n");
		close(_sock);
		return;
	}
	while(1){
		memset(buf,'\0',BUFFER_SIZE);
		printf("input a word : ");
		scanf("%s",buf);
		if(buf[0]=='q'){
			break;
		}
		n=send(_sock,buf,strlen(buf),0);
		if(n<=0){
			perror("client send failed\n");
			break;
		}
		usleep(1000);
		n=recv(_sock,buf,BUFFER_SIZE,0);
		if(n<=0){
			perror("client recv failed\n");
			break;
		}
		pthread_t tid=0;
		memcpy(&tid,buf,sizeof(tid));
		printf("client recv msg from %d \n",tid);
	}
	close(_sock);
}
