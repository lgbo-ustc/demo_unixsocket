#Source file  
SRC_SERVER = servermain.cpp server.cpp serverthread.cpp serverthreada.cpp serverthreadfactory.cpp 
SRC_CLIENT = client.cpp clientmain.cpp 
#Object file  
OBJ_SERVER = $(SRC_SERVER:.cpp=.o)  
OBJ_CLIENT = $(SRC_CLIENT:.cpp=.o)
#Output execution file  
PROGRAM_SERVER = server 
PROGRAM_CLIENT = client
#Compiler  
CC = g++  
#Include  
INCLUDE = -I/usr/include/ncurses -I/usr/include/  
#Linker Parameter  
LINKPARAM = -lpthread  
#Options for development  
#CFLAGS = -ansi -g -Wall  
#Options for release  
CFLAGS = -ansi -O -Wall  
all : $(PROGRAM_SERVER)  $(PROGRAM_CLIENT)
: $(PROGRAM_SERVER)  
$(PROGRAM_SERVER) : $(OBJ_SERVER)  
	$(CC) -o $(PROGRAM_SERVER)  $(OBJ_SERVER) $(LINKPARAM)  
: $(PROGRAM_CLIENT)
$(PROGRAM_CLIENT) : $(OBJ_CLIENT)
	$(CC) -o $(PROGRAM_CLIENT) $(OBJ_CLIENT) $(LINKPARAM)
SUFFIXES : .cpp  
cpp.o:  
	$(CC) $(INCLUDE) $(CFLAGS) $(LINKPARAM) -c $< 

clean: 
	-rm *.o 
