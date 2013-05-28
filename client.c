#include"config.h"

#define BUF_SIZE 10
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
		memset(buf,'\0',BUF_SIZE);
		buf[BUF_SIZE-1]='\0';
		scanf("%s",buf);
		n=send(s,buf,strlen(buf),0);
		if(n<=0){
			perror("client:send() failed");
			break;
		}
		printf("client send msg:%s %d\n",buf,n);
		if(buf[0]=='q'){
			break;
		}
		
		usleep(1000);
		n=recv(s,buf,BUF_SIZE,0);
		if(n<=0){
			perror("client:recv() failed");
			break;
		}
		printf("client : recieve msg: %s\n",buf);

	}
	close(s);
	return 0;
}

