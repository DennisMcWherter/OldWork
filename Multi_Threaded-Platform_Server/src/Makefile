# Makefile by Dennis J. McWherter, Jr.
CC=g++
CFLAGS=-Wall
LDLIBS=-lpthread


all: IRC.o ThreadManager.o Sockets.o main.o
	$(CC) $(CFLAGS) $(LDLIBS) main.o Threads/ThreadManager.o Sockets/Sockets.o IRC/IRC.o -o m_server

IRC.o:
	$(CC) $(CFLAGS) IRC/IRC.cpp -c -o IRC/IRC.o

ThreadManager.o:
	$(CC) $(CFLAGS) $(LDLIBS) Threads/ThreadManager.cpp -c -o Threads/ThreadManager.o

Sockets.o:
	$(CC) $(CFLAGS) Sockets/Sockets.cpp -c -o Sockets/Sockets.o

main.o:
	$(CC) $(CFLAGS) main.cpp -c -o main.o

clean:
	rm -rf m_server *.o Sockets/*.o Threads/*.o
