#Source file  
SRC = servermain.cpp server.cpp serverthread.cpp serverthreada.cpp serverthreadfactory.cpp  
#Object file  
OBJ = $(SRC:.cpp=.o)  
#Output execution file  
PROGRAM = server 
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
: $(PROGRAM)  
$(PROGRAM) : $(OBJ)  
	$(CC) -o $(PROGRAM)  $(OBJ) $(LINKPARAM)  
SUFFIXES : .cpp  
cpp.o:  
	$(CC) $(INCLUDE) $(CFLAGS) $(LINKPARAM) -c $< 
clean: 
	-rm *.o 
