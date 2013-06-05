#include"serverthreadfactory.h"
#include"serverthreada.h"

ServerThread * ServerThreadFactory::createThread(int flag){
	ServerThread * th;
	switch(flag){
		case 1 : th =(ServerThread*) new ServerThreadA();
				 break;
		default: th =(ServerThread*) new ServerThreadA;
				 break;
	}
	return th;
}
