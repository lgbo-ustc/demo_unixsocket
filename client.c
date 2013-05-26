#include"config.h"

#define BUF_SIZE 100
int main(){
	int len,n;
	int s; 
	struct sockaddr_un remote;
	char buf[BUF_SIZE];
	if((s=socket(AF_UNIX,SOCK_STREAM,0))==-1){
		perror("client:socket() failed");
		exit(1);
	}
	printf("client: trying to connect ...\n");
	remote.sun_family=AF_UNIX;
	strcpy(remote.sun_path,SOCKET_PATH);
	len=strlen(remote.sun_path)+sizeof(remote.sun_family);
	if((connect(s,(struct sockaddr*)&remote,len))==-1){
		perror("client:connect() failed");
		exit(1);
	}
	printf("client:connected\n");
	while(1){
		memset(buf,'q',BUF_SIZE);
		buf[BUF_SIZE-1]='\0';
		scanf("%s",buf);
		if(buf[0]=='q'){
			break;
		}
		if((n=send(s,buf,len,BUF_SIZE))==-1){
			perror("client:send() failed");
			break;
		}
		usleep(1000);
		if((n=recv(s,buf,BUF_SIZE,0))==-1){
			perror("client:recv() failed");
			break;
		}
		printf("client : recieve msg: %s\n",buf);

	}
	close(s);
	return 0;
}

