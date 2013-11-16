# Logonserver Makefile
# 1/6/11
#
# @author RageD (Dennis J. McWherter, Jr.)
CXX=g++
CXX_INC=-I../Libraries/POCO/include -I./include -I../Server-Shared/include -I../Libraries/MySQL/Linux/include/ -I../Client_Server-Shared/include/
CXX_LIBS=-lPocoMySQL -lPocoData -lPocoFoundation -lPocoNetSSL
CXXFLAGS=-Wall
OBJS=../Server-Shared/src/BaseSQL.o ../Server-Shared/src/Configuration.o src/LogonDB.o src/EventHandler.o src/Server.o src/PacketHandler.o src/PrivateKeyHandler.o src/main.o

all: $(OBJS)
	@echo "Building logon server..."
	$(CXX) $(CXXFLAGS) $(CXX_INC) $(CXX_LIBS) $(OBJS) -o bin/logonserver

%.o: %.cpp
	@echo "Building $*.o..."
	$(Q)$(CXX) $(CXXFLAGS) -O2 $(CXX_INC) $(CXX_LIBS) -c -o $@ $<

clean:
	@echo "Cleaning up..."
	rm -rf *.o src/*.o ../Server-Shared/src/*.o bin/logonserver
