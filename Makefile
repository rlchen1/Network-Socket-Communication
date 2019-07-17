########################################################################
# Makefile for Team07's Medieval Warfare Chess Program
#
# Makes the executable "Chess" using obj, dependency on 4 files
# Cleans obj files, log.txt files, and executable
######################################################################### 

CC = gcc
CFLAGS = -Wall -ansi -std=gnu99 -c
LFLAGS = -Wall -std=gnu99 #c99 changed to gnu99 to handle "warning: run with XOPEN_SRC"
TEST = -g -DDEBUG

####################GUI TEST################################################
GTKINC  = `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS = `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

INC  = $(GTKINC)
LIBS = $(GTKLIBS)
OPTS = -g

#GUI: ./bin/GUI.o
#	gcc ./bin/GUI.o $(LIBS) $(OPTS) -o ./bin/GUI
#./bin/GUI.o: ./src/GUI.c ./src/GUI.h
#	gcc -c ./src/GUI.c $(INC) $(OPTS) -o ./bin/GUI.o
#gui = guiTest
#GUI: $(gui)

#guiTest.o: guiTest.c guiTest.h
#	gcc $(CFLAGS) guiTest.c $(INC) $(OPTS) -o guiTest.o

#use "make GUI" to create the executable
#guiTest: guiTest.o
#	gcc -Wall guiTest.o $(LIBS) $(OPTS) -o guiTest
#############################################################################
OBJS = ./bin/AIStrategies.o ./bin/CheckDestination.o ./bin/CheckMovement.o ./bin/Chess.o 
DEPS = ./src/AIStrategies.h ./src/CheckDestination.h ./src/CheckMovement.h ./src/Constants.h 

LOBJS = ./bin/AIStrategies.o ./bin/CheckDestination.o ./bin/CheckMovement.o  
LDEPS = ./src/AIStrategies.h ./src/CheckDestination.h ./src/CheckMovement.h ./src/Chess.h

DESIGN = ./bin/Client ./bin/Server

all: $(DESIGN)

#chess: $(OBJS) $(DEPS)
#	$(CC) $(LFLAGS) $(OBJS) -o ./bin/chess

./bin/AIStrategies.o: ./src/AIStrategies.c $(DEPS)
	$(CC) $(CFLAGS) ./src/AIStrategies.c -o ./bin/AIStrategies.o
./bin/CheckDestination.o: ./src/CheckDestination.c $(DEPS)
	$(CC) $(CFLAGS) ./src/CheckDestination.c -o ./bin/CheckDestination.o
./bin/CheckMovement.o: ./src/CheckMovement.c $(DEPS)
	$(CC) $(CFLAGS) ./src/CheckMovement.c -o ./bin/CheckMovement.o
#./bin/Chess.o: ./src/Chess.c $(DEPS)
#	$(CC) $(CFLAGS) ./src/Chess.c -o ./bin/Chess.o

#################################    CHAT    ##################################
COBJS = ./bin/chat.o ./bin/Client.o ./bin/Server.o ./bin/GUI.o ./bin/Chess.o
CDEPS = ./src/Constants.h ./src/Client.h ./src/Server.h ./src/UserInfo.h ./src/User.h ./src/UserList.h ./src/GUI.h ./src/Chess.h
# make
test: ./bin/Client ./bin/Server

chat: $(COBJS) $(CDEPS) 
	$(CC) $(LFLAGS) $(COBJS) -o ./bin/chat
./bin/chat.o: ./src/chat.c $(CDEPS)
	$(CC) $(CFLAGS) ./src/chat.c -o ./bin/chat.o
./bin/GUI.o: ./src/GUI.c $(CDEPS)
	$(CC) $(CFLAGS) ./src/GUI.c $(INC) $(OPTS) -o ./bin/GUI.o
./bin/Chess.o: ./src/Chessv2.c $(LDEPS)
	$(CC) $(CFLAGS) ./src/Chessv2.c -o ./bin/Chess.o
./bin/Client.o: ./src/client.c $(CDEPS)
	$(CC) $(CFLAGS) ./src/client.c $(INC) $(OPTS) -o ./bin/Client.o 
./bin/Client: ./bin/Client.o ./bin/GUI.o ./bin/Chess.o $(CDEPS) $(LDEPS) $(LOBJS)
	$(CC) ./bin/Client.o ./bin/GUI.o ./bin/Chess.o $(LFLAGS) $(LIBS) $(OPTS) $(LOBJS) -o ./bin/Client
./bin/Server.o: ./src/server.c $(CDEPS) 
	$(CC) $(CFLAGS) ./src/server.c -o ./bin/Server.o
./bin/Server: ./bin/Server.o ./bin/User.o ./bin/UserList.o $(CDEPS) $(LDEPS)
	$(CC) ./bin/Server.o ./bin/User.o ./bin/UserList.o $(LFLAGS) -o ./bin/Server
./bin/User.o: ./src/User.c $(CDEPS)
	$(CC) $(CFLAGS) ./src/User.c -o ./bin/User.o
./bin/UserList.o: ./src/UserList.c $(CDEPS)
	$(CC) $(CFLAGS) ./src/UserList.c -o ./bin/UserList.o

###############################################################################
clean: 
	rm -f ./bin/*.o `find . -wholename ./bin/'*.txt' ! -wholename ./bin/'UserData.txt' ! -wholename ./bin/'MSG.txt'`  $(gui) ./bin/chat ./bin/Client ./bin/Server ./bin/link ./bin/GUI
#this cleans except for "UserData.txt" file within the bin directory 
tar:
	tar zcvf Chat_Beta_src.tar.gz src bin doc Makefile COPYRIGHT INSTALL README
