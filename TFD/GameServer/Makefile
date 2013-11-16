# Gameserver Makefile
# 1/6/11
#
# @author RageD (Dennis J. McWherter, Jr.)
CXX=g++
CXX_INC=-L../Libraries/Enet/lib/Linux -I../Libraries/Enet/include -I../Libraries/Enetpp2/include -I../Libraries/POCO/include -I./include -I../Server-Shared/include -I../Libraries/MySQL/Linux/include/
CXX_LIBS=-lenet -lPocoMySQL -lPocoData -lPocoFoundation
CXXFLAGS=-Wall
OBJS=../Server-Shared/src/BaseSQL.o src/Server.o src/ConnectionHandler.o src/Connection.o src/main.o
DEPS=../Libraries/Enetpp2/src/ENet.o ../Libraries/Enetpp2/src/Host.o ../Libraries/Enetpp2/src/Address.o ../Libraries/Enetpp2/src/Event.o ../Libraries/Enetpp2/src/Packet.o ../Libraries/Enetpp2/src/Peer.o

all: $(OBJS)
	@echo "Building game server..."
	$(CXX) $(CXXFLAGS) $(CXX_INC) $(CXX_LIBS) $(DEPS) $(OBJS) -o bin/gameserver

%.o: %.cpp
	@echo "Building $*.o..."
	$(Q)$(CXX) $(CXXFLAGS) $(CXX_INC) $(CXX_LIBS) -O2 -c -o $@ $<

clean:
	@echo "Cleaning up..."
	rm -rf *.o src/*.o ../Server-Shared/src/*.o bin/gameserver
