# Gameserver Makefile
# 1/6/11
#
# @author RageD (Dennis J. McWherter, Jr.)
CXX=g++
CXX_INC=-L../Libraries/Enet/lib/Linux -I../Libraries/Enet/include -I../Libraries/Enetpp2/include -I../Libraries/POCO/include/Poco -I./include -I../Server-Shared/include -I../LoginServer/include -I../Client_Server-Shared/include
CXX_LIBS=-lenet -lPocoMySQL -lPocoData -lPocoFoundation -lPocoNetSSL
CXXFLAGS=-Wall
DEPS=../Libraries/Enetpp2/src/ENet.o ../Libraries/Enetpp2/src/Host.o ../Libraries/Enetpp2/src/Address.o ../Libraries/Enetpp2/src/Event.o ../Libraries/Enetpp2/src/Packet.o ../Libraries/Enetpp2/src/Peer.o

all: server login

server: debug-server_client.o
	@echo "Building gameserver debugging client..."
	$(CXX) $(CXXFLAGS) $(CXX_INC) $(CXX_LIBS) $(DEPS) debug-server_client.o -o debug-server_client

login: debug-login_client.o
	@echo "Building loginserver debugging client..."
	$(CXX) $(CXXFLAGS) $(CXX_INC) $(CXX_LIBS) $(DEPS) debug-login_client.o -o debug-login_client

%.o: %.cpp
	@echo "Building $*.o..."
	$(CXX) $(CXXFLAGS) -O2 $(CXX_INC) $(CXX_LIBS) -c -o $@ $<

clean:
	@echo "Cleaning up..."
	rm -rf *.o debug-server_client debug-login_client
